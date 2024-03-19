/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:52:09 by ctruchot          #+#    #+#             */
/*   Updated: 2024/03/19 14:00:51 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env_parsing.h"
#include "exec.h"
#include "file_checks.h"
#include <sys/wait.h> 

int	exec(t_cmd *cmd, char **mini_env)
{
	t_exec exec;

	if (initialize_exec(&exec, cmd, mini_env) != 0)
		return (1); // gerer
	// if (exec.total_cmd == 1)
	// {
	// 	exec.pid = fork();
	// 	if (exec.pid < 0)
	// 		return (ft_putstr_fd(strerror(errno), 2), 2);
	// 	if (exec.pid == 0)
	// 		exec_uno(cmd, mini_env);
	// 	waitpid(exec.pid, NULL, 0);
	// }
	if (exec.total_cmd > 1)
	{
		if (create_pipes(&exec, exec.total_cmd) != 0)
			return (1); // parent clean only
		if (ft_fork(&exec) != 0)
			return (1); // parent clean only
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
	int fdin;
	int fdout;

	if (cmd->in != NULL)
	{
		fdin = open(cmd->in->path, O_RDONLY);
		if (fdin < 0)
			return(1);
		if (dup2(fdin, STDIN_FILENO) == -1)
			return (1); // revoir le return clean_exit_cmd()
	}
	if (cmd->out != NULL)
	{
		fdout = open(cmd->out->path, O_WRONLY);
		if (fdout < 0)
			return(1);
		if (dup2(fdout, STDOUT_FILENO) == -1)
			return (1); // revoir le return
	}
	if (cmd->argv == NULL)
		return (1);
	close(fdin);
	close(fdout);
	if (execve(cmd->path_cmd, cmd->argv, mini_env) == -1)
		return (1);
	return (0);
}
