/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 19:40:29 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/21 13:56:59 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	exec_env_c(t_exec *exec, t_child *child)
{
	int	i;

	i = 0;
	if (!child->current_cmd->argv[1])
	{
		while (exec->mini_env[i])
		{
			ft_printf("%s\n", exec->mini_env[i]);
			i++;
		}
		clear_built(exec, child, 0);
	}
	// on peut ignorer ou erreur si argv[1]
	else
		clear_built(exec, child, msg_built(ENV, 1));
}

void	exec_env(t_exec *exec)
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
		clean_exit_parent(exec, 0);
	}
	// on peut ignorer ou erreur si argv[1]
	else
		clean_exit_parent(exec, msg_built(ENV, 0));
}

void	exec_exit_c(t_exec *exec, t_child *child)
{
	ft_printf("exit\n");
	clear_built(exec, child, 0);
}

void	exec_exit_parent(t_exec *exec)
{
	ft_printf("exit\n");
	rl_clear_history();
	final_exit(exec, 0);
}
