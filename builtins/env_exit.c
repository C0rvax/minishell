/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 19:40:29 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/23 18:33:50 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	str_isdigit(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while(str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	exec_env_c(t_exec *exec, t_child *child)
{
	int		i;
	char	**argv;

	i = 0;
	argv = child->current_cmd->argv;
	if (!argv[1])
	{
		while (exec->mini_env[i])
		{
			ft_printf("%s\n", exec->mini_env[i]);
			i++;
		}
		clear_built(exec, child, 0);
	}
	else
		clear_built(exec, child, msg_built(ENV, argv[1], 1));
}

int	exec_env(t_exec *exec)
{
	int	i;

	i = 0;
	if (!exec->cmd->argv[1])
	{
		while (exec->mini_env[i])
		{
			ft_printf("%s\n", exec->mini_env[i]);
			i++;
		}
		return (clean_exit_parent(exec, 0));
	}
	else
		return (clean_exit_parent(exec, msg_built(ENV, exec->cmd->argv[1], 1)));
}

void	exec_exit_c(t_exec *exec, t_child *child)
{
	char	**argv;

	argv = child->current_cmd->argv;
	ft_printf("exit\n");
	if (argv[1])
	{
		if (argv[2])
			clear_built(exec, child, msg_built(ARGS, "exit", 1));
		else if (str_isdigit(argv[1]))
			clear_built(exec, child, ft_atoi(argv[1]));
		else
			clear_built(exec, child, msg_built(EXIT, argv[1], 2));
	}
	clear_built(exec, child, 0);
}

void	exec_exit_parent(t_exec *exec)
{
	ft_printf("exit\n");
	if (exec->cmd->argv[1])
	{
		if (exec->cmd->argv[2])
			final_exit(exec, msg_built(ARGS, "exit", 1));
		else if (str_isdigit(exec->cmd->argv[1]))
			final_exit(exec, ft_atoi(exec->cmd->argv[1]));
		else
			final_exit(exec, msg_built(EXIT, exec->cmd->argv[1], 2));
	}
	final_exit(exec, 0);
}
