/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_fds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:07:39 by ctruchot          #+#    #+#             */
/*   Updated: 2024/04/15 19:09:11 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

#include "builtin.h"
#include "file_checks.h"
#include "minishell.h"

void	close_higher_fds(t_exec *exec)
{
	int	l;

	l = exec->cmdno + 1;
	while (l < exec->total_cmd - 1)
	{
		close(exec->fd[l][0]);
		close(exec->fd[l][1]);
		l++;
	}
	close(exec->fd[exec->cmdno][0]);
}

static int	find_fdout(t_exec *exec, t_child *child)
{
	if (child->current_cmd->out->mode == SIMPLE)
		child->fdout = open(child->current_cmd->out->path, O_WRONLY | O_TRUNC);
	else if (child->current_cmd->out->mode == DOUBLE)
		child->fdout = open(child->current_cmd->out->path, O_WRONLY | O_APPEND);
	if (child->fdout < 0)
		return (clean_exit_fds(exec, child), 1);
	return (0);
}

int	manage_fd_firstchild(t_exec *exec, t_child *child)
{
	if (!child->current_cmd->out)
		child->fdout = exec->fd[0][1];
	else
	{
		if (find_fdout(exec, child) != 0)
			return (1);
		close(exec->fd[child->cmdno][1]);
	}
	if (dup2(child->fdout, STDOUT_FILENO) == -1)
		return (clean_exit_fds(exec, child), 1);
	close(child->fdout);
	if (child->current_cmd->in)
	{
		child->fdin = open(child->current_cmd->in->path, O_RDONLY);
		if (child->fdin < 0)
			return (clean_exit_fds(exec, child), 1);
		if (dup2(child->fdin, STDIN_FILENO) == -1)
			return (clean_exit_fds(exec, child), 1);
		close(child->fdin);
	}
	return (0);
}

int	manage_fd_middlechild(t_exec *exec, t_child *child)
{
	close(exec->fd[child->cmdno - 1][1]);
	if (!child->current_cmd->in)
		child->fdin = exec->fd[child->cmdno - 1][0];
	else
	{
		child->fdin = open(child->current_cmd->in->path, O_RDONLY);
		if (child->fdin < 0)
			return (clean_exit_fds(exec, child), 1);
		close(exec->fd[child->cmdno - 1][0]);
	}
	if (dup2(child->fdin, STDIN_FILENO) == -1)
		return (clean_exit_fds(exec, child), 1);
	close(child->fdin);
	if (!child->current_cmd->out)
		child->fdout = exec->fd[child->cmdno][1];
	else
	{
		if (find_fdout(exec, child) != 0)
			return (1);
		close(exec->fd[child->cmdno][1]);
	}
	if (dup2(child->fdout, STDOUT_FILENO) == -1)
		return (clean_exit_fds(exec, child), 1);
	close(child->fdout);
	return (0);
}

int	manage_fd_lastchild(t_exec *exec, t_child *child)
{
	close(exec->fd[child->cmdno - 1][1]);
	if (!child->current_cmd->in)
		child->fdin = exec->fd[child->cmdno - 1][0];
	else
	{
		child->fdin = open(child->current_cmd->in->path, O_RDONLY);
		if (child->fdin < 0)
			return (clean_exit_fds(exec, child), 1);
		close(exec->fd[child->cmdno - 1][0]);
	}
	if (dup2(child->fdin, STDIN_FILENO) == -1)
		return (clean_exit_fds(exec, child), 1);
	close(child->fdin);
	if (child->current_cmd->out)
	{
		if (find_fdout(exec, child) != 0)
			return (1);
		if (dup2(child->fdout, STDOUT_FILENO) == -1)
			return (clean_exit_fds(exec, child), 1);
		close(child->fdout);
	}
	return (0);
}
