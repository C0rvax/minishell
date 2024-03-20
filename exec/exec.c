/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:52:09 by ctruchot          #+#    #+#             */
/*   Updated: 2024/03/20 17:59:31 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env_parsing.h"
#include "exec.h"
#include "file_checks.h"
#include <sys/wait.h> 
#include "builtin.h"

int	exec(t_cmd *cmd, char **mini_env)
{
	t_exec exec;

	if (initialize_exec(&exec, cmd, mini_env) != 0)
		return (1); // gerer
	ft_printf("total_cmd =%d\n", exec.total_cmd);
	if (exec.total_cmd == 1)
	{
		if (exec.cmd->type != KILLED)
		{
			is_exit(&exec); // doit-on le sortir de la condition KILLED ?
			exec.pid[0] = fork();
			if (exec.pid[0] < 0)
				return (ft_putstr_fd(strerror(errno), 2), 2);
			if (exec.pid[0] == 0)
				exec_uno(cmd, mini_env);
			waitpid(exec.pid[0], NULL, 0);
			clean_exit_parent(&exec, 0);
		}
		else if (exec.cmd->type == KILLED)
			clean_exit_parent(&exec, 0);
	}
	else if (exec.total_cmd > 1)
	{
		if (create_pipes(&exec, exec.total_cmd) != 0)
			return (1); // parent clean only
		if (ft_fork(&exec) != 0)
			return (1); // SI ENFANT KILLED 
		clean_end(&exec);
	}
	return (0);
}

 int initialize_exec(t_exec *exec, t_cmd *cmd, char **mini_env)
{
	int	k;

	k = -1;
	ft_bzero(exec, sizeof(t_exec));
	exec->total_cmd = ft_cmd_lstsize(cmd);
	exec->fd = malloc(sizeof(int *) * exec->total_cmd - 1);
	if (!exec->fd)
		return (clean_exit_parent(exec, 1), 1);
	while (++k < exec->total_cmd - 1)
	{
		exec->fd[k] = malloc(sizeof(int) * 2);
		if (!exec->fd[k])
			return (clean_exit_parent(exec, 1), 1);
	}
	exec->pid = malloc(sizeof(int) * exec->total_cmd);
	if (!exec->pid)
		return (clean_exit_parent(exec, 1), 1);
	exec->cmd = cmd; // free cmd et mini_env la plus haut dans la chaine ?
	exec->mini_env = mini_env;
	return (0);
}

int	exec_uno(t_cmd *cmd, char **mini_env)
{
	int fdin; // initialiser
	int fdout;

	if (cmd->argv == NULL)
		return (1);
	if (cmd->in != NULL)
	{
		fdin = open(cmd->in->path, O_RDONLY);
		if (fdin < 0)
			return(1);
		if (dup2(fdin, STDIN_FILENO) == -1)
			return (1); // revoir le return clean_exit_cmd()
		close(fdin);
	}
	if (cmd->out != NULL)
	{
		fdout = open(cmd->out->path, O_WRONLY);
		if (fdout < 0)
			return(1);
		if (dup2(fdout, STDOUT_FILENO) == -1)
			return (1); // revoir le return
		close(fdout);
	}
	// exec_builtin(exec, child);
	if (execve(cmd->path_cmd, cmd->argv, mini_env) == -1)
		return (1);
	return (0);
}
