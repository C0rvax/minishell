/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:05:06 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/21 14:08:34 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	check_flag_echo(char *str)
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
		i = 0;
		while (buf[++i])
			ft_printf("%s", buf[i]);
	}
	else if (buf[1] && check_flag_echo(buf[1]))
	{
		i = 0;
		while (buf[++i])
			ft_printf("%s", buf[i]);
		ft_printf("\n");
	}
	clear_built(exec, child, 0);
}

void	exec_echo(t_exec *exec)
{
	int		i;
	char	**buf;

	buf = exec->cmd->argv;
	i = 1;
	if (!buf[1])
		ft_printf("\n");
	else if (buf[1] && !check_flag_echo(buf[1]))
	{
		i = 0;
		while (buf[++i])
			ft_printf("%s", buf[i]);
	}
	else if (buf[1] && check_flag_echo(buf[1]))
	{
		i = 0;
		while (buf[++i])
			ft_printf("%s", buf[i]);
		ft_printf("\n");
	}
	clean_exit_parent(exec, 0);
}
