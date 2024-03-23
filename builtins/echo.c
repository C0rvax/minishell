/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:05:06 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/23 14:57:08 by aduvilla         ###   ########.fr       */
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

void	exec_echo_c(t_exec *exec, t_child *child)
{
	int		i;
	char	**buf;

	buf = child->current_cmd->argv;
	if (!buf[1])
		ft_printf("\n");
	else if (buf[1] && !check_flag_echo(buf[1]))
	{
		i = 1;
		while (buf[i] && !check_flag_echo(buf[i]))
			i++;
		while (buf[i])
		{
			ft_printf("%s", buf[i]);
			i++;
		}
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
	if (!buf[1])
		ft_printf("\n");
	else if (buf[1] && !check_flag_echo(buf[1]))
	{
		i = 1;
		while (buf[i] && !check_flag_echo(buf[i]))
			i++;
		while (buf[i])
		{
			ft_printf("%s", buf[i]);
			i++;
		}
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
