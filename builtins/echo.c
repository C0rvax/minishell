/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:05:06 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/27 17:07:56 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	check_flag_echo(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (1);
	while (str[++i])
	{
		if (str[i] != 'n')
			return (1);
	}
	return (0);
}

static void	print_echo(char **buf, int i, int fd)
{
	int	j;

	j = 0;
	while (buf[i])
	{
		if (j > 0)
			ft_putstr_fd(" ", fd);
		ft_putstr_fd(buf[i], fd);
		i++;
		j++;
	}
}

void	exec_echo_c(t_exec *exec, t_child *child)
{
	int		i;
	char	**buf;

	buf = child->current_cmd->argv;
	i = 1;
	if (!buf[1])
		ft_printf("\n");
	else if (buf[1] && !check_flag_echo(buf[1]))
	{
		while (buf[i] && !check_flag_echo(buf[i]))
			i++;
		print_echo(buf, i, 1);
	}
	else if (buf[1] && check_flag_echo(buf[1]))
	{
		print_echo(buf, i, 1);
		ft_printf("\n");
	}
	clear_built(exec, child, 0);
	exit(1);
}

int	exec_echo(t_exec *exec)
{
	int		i;
	int		fd;
	char	**buf;

	fd = redirect_out(exec);
	if (fd < 0)
		return (clear_one(exec, msg_built(FD, exec->cmd->argv[1], 1)));
	buf = exec->cmd->argv;
	i = 1;
	if (!buf[1])
		ft_putstr_fd("\n", fd);
	else if (buf[1] && !check_flag_echo(buf[1]))
	{
		while (buf[i] && !check_flag_echo(buf[i]))
			i++;
		print_echo(buf, i, fd);
	}
	else if (buf[1] && check_flag_echo(buf[1]))
	{
		print_echo(buf, i, fd);
		ft_putstr_fd("\n", fd);
	}
	if (fd != 1)
		close(fd);
	return (clear_one(exec, 0));
}
