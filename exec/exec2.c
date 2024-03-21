/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:22:00 by ctruchot          #+#    #+#             */
/*   Updated: 2024/03/21 16:09:40 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env_parsing.h"
#include "exec.h"
#include "file_checks.h"
#include "builtin.h"

int	create_pipes(t_exec *exec, int total_cmd)
{
	int	l;

	l = 0;
	while (l < total_cmd - 1)
	{
		if (pipe(exec->fd[l]) == -1)
			return (close_all_fds(exec), clean_exit_parent(exec, 1), 1); // inclure le close all ds exit_parents ?
		l++;
	}
	return (0);
}

int	ft_fork(t_exec *exec)
{
	int k = -1;
	while (exec->cmdno < exec->total_cmd)
	{
		exec->pid[exec->cmdno] = fork();
		if (exec->pid[exec->cmdno] < 0)
			return (close_all_fds(exec), clean_exit_parent(exec, 1), 2);
		if (exec->pid[exec->cmdno] == 0)
		{
			t_child child;
			initialize_child(&child, exec);
			if (child.current_cmd->type == KILLED)
				return (close_all_fds(exec), clean_exit_child(exec, 0), 1);
			if (redirect_pipes(exec, &child) != 0)
				return (1); // ds quel cas - child killed OK
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

int	redirect_pipes(t_exec *exec, t_child *child)
{
	if (exec->cmdno == 0)
		if (manage_fd_firstchild(exec, child) != 0)
			return (1); // qd fd ou dup merde
	if (exec->cmdno > 0 && exec->cmdno < exec->total_cmd - 1)
		if (manage_fd_middlechild(exec, child) != 0)
			return (1); // free(child)
	if (exec->cmdno == exec->total_cmd - 1)
		if (manage_fd_lastchild(exec, child) != 0)
			return (1); // free(child)
	exec_builtin(exec, child);
	if (execve(child->current_cmd->path_cmd, child->current_cmd->argv, exec->mini_env) == -1)
		return (1); // free(child)
	return (0);
}

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

int manage_fd_firstchild(t_exec *exec, t_child *child)
{
	close_higher_fds(exec);
	if (!child->current_cmd->out)
		child->fdout = exec->fd[0][1];
	else
	{
		if (child->current_cmd->out->mode == SIMPLE)
			child->fdout = open(child->current_cmd->out->path, O_WRONLY | O_TRUNC);
		else if (child->current_cmd->out->mode == DOUBLE)
			child->fdout = open(child->current_cmd->out->path, O_WRONLY | O_APPEND);
		if (child->fdout < 0)
			return (clean_exit_fds(exec, child), 1); // revoir si fds relevant
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
		close (child->fdin);
	}
	return (0);
}

int manage_fd_middlechild(t_exec *exec, t_child *child)
{
	close_higher_fds(exec);
	close(exec->fd[child->cmdno - 1][1]);
	if (!child->current_cmd->in)
		child->fdin = exec->fd[child->cmdno - 1][0];
	else
	{
		child->fdin = open(child->current_cmd->in->path, O_RDONLY);
		if (child->fdin < 0)
			return (clean_exit_fds(exec, child), 1);
	}
	if (dup2(child->fdin, STDIN_FILENO) == -1)
		return (clean_exit_fds(exec, child), 1);
	close(child->fdin);
	if (!child->current_cmd->out)
	{
		// close(exec->fd[child->cmdno][1]);
		child->fdout = exec->fd[child->cmdno][1];
		// // ft_putstr_fd("fdoutchild0=\n", 2);
		// ft_putnbr_fd(child->fdout, 2);
	}
	else
	{
		if (child->current_cmd->out->mode == SIMPLE)
			child->fdout = open(child->current_cmd->out->path, O_WRONLY | O_TRUNC);
		else if (child->current_cmd->out->mode == DOUBLE)
			child->fdout = open(child->current_cmd->out->path, O_WRONLY | O_APPEND);
		if (child->fdout < 0)
			return (clean_exit_fds(exec, child), 1); // revoir si fds relevant et clean child
	}
	if (dup2(child->fdout, STDOUT_FILENO) == -1)
		return (clean_exit_fds(exec, child), 1);
	close(child->fdout);
	return (0);
}

int manage_fd_lastchild(t_exec *exec, t_child *child)
{
	// close_higher_fds(exec); // close lower ?? 
	close(exec->fd[child->cmdno - 1][1]);
	if (!child->current_cmd->in)
		child->fdin = exec->fd[child->cmdno - 1][0];
	else
	{
		child->fdin = open(child->current_cmd->in->path, O_RDONLY);
		if (child->fdin < 0)
			return (clean_exit_fds(exec, child), 1); // gerer
	}
	// ft_printf("fdin child1=%d\n", child->fdin);
	if (dup2(child->fdin, STDIN_FILENO) == -1)
		return (clean_exit_fds(exec, child), 1);
	close(child->fdin);
	if (child->current_cmd->out)
	{
		if (child->current_cmd->out->mode == SIMPLE)
			child->fdout = open(child->current_cmd->out->path, O_WRONLY | O_TRUNC);
		else if (child->current_cmd->out->mode == DOUBLE)
			child->fdout = open(child->current_cmd->out->path, O_WRONLY | O_APPEND);
		if (child->fdout < 0)
			return (clean_exit_fds(exec, child), 1); // revoir si fds relevant et clean child
	}
	else
		child->fdout = STDOUT_FILENO;
	if (dup2(child->fdout, STDOUT_FILENO) == -1)
		return (clean_exit_fds(exec, child), 1);
	close (child->fdout);
	// ft_putstr_fd("fdout child1=\n", 2);
	// ft_putnbr_fd(child->fdout, 2);
	return (0);
}

