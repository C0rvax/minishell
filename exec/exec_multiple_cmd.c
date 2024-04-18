/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multiple_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:22:00 by ctruchot          #+#    #+#             */
/*   Updated: 2024/04/18 17:23:41 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

#include "minishell.h" // garder tous ces headers?
#include "builtin.h"
#include "file_checks.h"

int	initialize_child(t_child *child, t_exec *exec)
{
	int	i;

	i = 0;
	ft_bzero(child, sizeof(t_child));
	child->cmdno = exec->cmdno;
	child->current_cmd = exec->cmd;
	if (child->cmdno > 0 && child->cmdno < exec->total_cmd)
	{
		while (i < child->cmdno)
		{
			child->current_cmd = child->current_cmd->next;
			i++;
		}
	}
	return (0);
}

static int	redirect(t_exec *exec, t_child *child)
{
	if (exec->cmdno == 0)
	{
		close_higher_fds(exec);
		if (manage_fd_firstchild(exec, child) != 0)
			return (1);
	}
	if (exec->cmdno > 0 && exec->cmdno < exec->total_cmd - 1)
	{
		close_higher_fds(exec);
		if (manage_fd_middlechild(exec, child) != 0)
			return (1);
	}
	if (exec->cmdno == exec->total_cmd - 1)
		if (manage_fd_lastchild(exec, child) != 0)
			return (1);
	exec_builtin(exec, child);
	if (execve(child->current_cmd->path_cmd, child->current_cmd->argv,
			exec->mini_env) == -1)
		return (1);
	return (0);
}

int	ft_fork(t_exec *exec)
{
	t_child	child;

	while (exec->cmdno < exec->total_cmd)
	{
		exec->pid[exec->cmdno] = fork();
		signals(4);
		if (exec->pid[exec->cmdno] < 0)
			return (close_all_fds(exec), clean_exit_parent(exec, 1), 2);
		if (exec->pid[exec->cmdno] == 0)
		{
			initialize_child(&child, exec);
			if ((child.current_cmd->type == KILLED) || redirect(exec, &child))
			{
				close_all_fds(exec);
				clean_exit_child(exec, &child, 0);
			}
		}
		if (exec->cmdno >= 1)
		{
			close(exec->fd[exec->cmdno - 1][0]);
			close(exec->fd[exec->cmdno - 1][1]);
		}
		exec->cmdno++;
	}
	return (0);
}

int	create_pipes(t_exec *exec, int total_cmd)
{
	int	l;

	l = 0;
	while (l < total_cmd - 1)
	{
		if (pipe(exec->fd[l]) == -1)
			return (close_all_fds(exec), clean_exit_parent(exec, 1), 1);
		l++;
	}
	return (0);
}
