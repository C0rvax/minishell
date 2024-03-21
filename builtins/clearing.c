/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clearing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:43:49 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/21 12:23:05 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	msg_built(t_built msg, int status_code)
{
	if (msg == BMALLOC)
		ft_putstr_fd("minishell: unexpected error: allocation failure\n", 2);
	if (msg == PWD)
		ft_putstr_fd("minishell: pwd: options are not handled\n", 2);
	return (status_code);
}

int	clear_built(t_exec *exec, t_child *child, int status_code)
{
	int	i;

	i = 0;
	ft_cmd_lstclear(&exec->cmd);
//	close_fd(exec->fd);
	while (exec->fd[i])
	{
		free(exec->fd[i]);
		i++;
	}
	free(exec->fd);
	free(exec->pid);
	ft_freetab(exec->mini_env);
	if (child)
		free(child);
	exit (status_code);
}

int	final_exit(t_exec *exec, int status_code)
{
	ft_cmd_lstclear(&exec->cmd);
//	close_fd(exec->fd);
	free(exec->fd);
	free(exec->pid);
	ft_freetab(exec->mini_env);
	exit (status_code);
}
