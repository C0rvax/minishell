/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:52:09 by ctruchot          #+#    #+#             */
/*   Updated: 2024/04/02 13:20:37 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "builtin.h"
#include "file_checks.h"
#include "minishell.h"

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

int	manage_fds(t_cmd *cmd)
{
	int	fdin;
	int	fdout;

	fdin = 0;
	fdout = 0;
	if (cmd->in != NULL)
	{
		fdin = open(cmd->in->path, O_RDONLY);
		if (fdin < 0)
			return (ft_putstr_fd(strerror(errno), 2), 1);
		if (dup2(fdin, STDIN_FILENO) == -1)
			return (ft_putstr_fd(strerror(errno), 2), 1);
		close(fdin);
	}
	if (cmd->out != NULL)
	{
		fdout = open(cmd->out->path, O_WRONLY);
		if (fdout < 0)
			return (ft_putstr_fd(strerror(errno), 2), 1);
		if (dup2(fdout, STDOUT_FILENO) == -1)
			return (ft_putstr_fd(strerror(errno), 2), 1);
		close(fdout);
	}
	return (0);
}

int	exec_uno(t_exec *exec)
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
		if (manage_fds(exec->cmd) != 0)
			return (1);
		if (execve(path_cmd, exec->cmd->argv, exec->mini_env) == -1)
			return (1);
	}
	waitpid(exec->pid[0], &status, 0);
	if (WIFEXITED(status))
		g_status = WEXITSTATUS(status);
	clean_exit_parent(exec, 0);
	return (g_status);
}

int	initialize_exec(t_exec *exec, t_cmd *cmd, char **mini_env)
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
	exec->mini_env = mini_env;
	return (0);
}

int	exec(t_cmd *cmd, t_persistent *pers)
{
	t_exec	exec;

	if (initialize_exec(&exec, cmd, pers->mini_env) != 0)
		return (1);
	if (exec.total_cmd == 1)
	{
		if (exec.cmd->type == KILLED)
			return (clean_exit_parent(&exec, 0), g_status);
			// return (clean_exit_parent(&exec, 0), pers->g_status);
		else if (exec.cmd->type == BUILTPAR)
			return (exec_builtin_parent(&exec, pers));
		else
			return (exec_uno(&exec));
	}
	else if (exec.total_cmd > 1)
	{
		if (create_pipes(&exec, exec.total_cmd) != 0)
			return (1);
		if (ft_fork(&exec) != 0)
			return (1);
		g_status = clean_end(&exec);
		// pers->g_status = clean_end(&exec, pers);

	}
	return (g_status);
	// return (pers->g_status);
}
