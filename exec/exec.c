/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:52:09 by ctruchot          #+#    #+#             */
/*   Updated: 2024/04/18 17:23:11 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "exec.h"
#include "file_checks.h"
#include "minishell.h"

static int	manage_fds_in(t_cmd *cmd)
{
	int	fdin;

	fdin = 0;
	if (cmd->in != NULL)
	{
		fdin = open(cmd->in->path, O_RDONLY);
		if (fdin < 0)
			return (ft_putstr_fd(strerror(errno), 2), 1);
		if (dup2(fdin, STDIN_FILENO) == -1)
			return (ft_putstr_fd(strerror(errno), 2), 1);
		close(fdin);
	}
	return (0);
}

static int	manage_fds_out(t_cmd *cmd)
{
	int	fdout;

	fdout = 0;
	if (cmd->out != NULL)
	{
		if (cmd->out->mode == SIMPLE)
			fdout = open(cmd->out->path, O_WRONLY | O_TRUNC);
		else if (cmd->out->mode == DOUBLE)
			fdout = open(cmd->out->path, O_WRONLY | O_APPEND);
		if (fdout < 0)
			return (ft_putstr_fd(strerror(errno), 2), 1);
		if (dup2(fdout, STDOUT_FILENO) == -1)
			return (ft_putstr_fd(strerror(errno), 2), 1);
		close(fdout);
	}
	return (0);
}

static int	exec_uno(t_exec *exec, t_pers *pers)
{
	int		status;
	char	*path_cmd;

	path_cmd = exec->cmd->path_cmd;
	if (!exec->cmd->argv || !exec->cmd->argv[0])
		return (1);
	exec->pid[0] = fork();
	signals(2);
	if (exec->pid[0] < 0)
		return (ft_putstr_fd(strerror(errno), 2), 1);
	if (exec->pid[0] == 0)
	{
		if (manage_fds_in(exec->cmd) != 0 || manage_fds_out(exec->cmd) != 0)
			return (1);
		if (execve(path_cmd, exec->cmd->argv, exec->mini_env) == -1)
			return (1);
	}
	waitpid(exec->pid[0], &status, 0);
	get_status(status, pers);
	clean_exit_parent(exec, 0);
	return (pers->status_code);
}

static int	initialize_exec(t_exec *exec, t_cmd *cmd, t_pers *pers)
{
	int	k;

	k = -1;
	ft_bzero(exec, sizeof(t_exec));
	exec->total_cmd = ft_cmd_lstsize(cmd);
	if (exec->total_cmd > 1)
	{
		exec->fd = malloc(sizeof(int *) * exec->total_cmd - 1);
		if (!exec->fd)
			return (clean_exit_parent(exec, 1));
		while (++k < exec->total_cmd - 1)
		{
			exec->fd[k] = malloc(sizeof(int) * 2);
			if (!exec->fd[k])
				return (clean_exit_parent(exec, 1));
		}
	}
	exec->pid = malloc(sizeof(int) * exec->total_cmd);
	if (!exec->pid)
		return (clean_exit_parent(exec, 1), 1);
	exec->cmd = cmd;
	exec->mini_env = pers->mini_env;
	exec->export = pers->export;
	return (0);
}

int	exec(t_cmd *cmd, t_pers *pers)
{
	t_exec	exec;

	if (initialize_exec(&exec, cmd, pers) != 0)
		return (1);
	if (exec.total_cmd == 1)
	{
		if (exec.cmd->type == KILLED)
			return (clean_exit_parent(&exec, 0), pers->status_code);
		else if (exec.cmd->type == BUILTPAR)
			return (exec_builtin_parent(&exec, pers));
		else
		{
			exec_builtin_parent(&exec, pers);
			return (exec_uno(&exec, pers));
		}
	}
	else if (exec.total_cmd > 1)
	{
		if (create_pipes(&exec, exec.total_cmd) != 0)
			return (1);
		if (ft_fork(&exec) != 0)
			return (1);
		pers->status_code = clean_end(&exec, pers);
	}
	return (pers->status_code);
}
