/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:52:09 by ctruchot          #+#    #+#             */
/*   Updated: 2024/03/21 17:55:35 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env_parsing.h"
#include "exec.h"
#include "file_checks.h"
#include <sys/wait.h> 
#include "builtin.h"

int	exec(t_cmd *cmd, t_persistent *pers)
{
	t_exec	exec;

	//gerer pers->status_code
	if (initialize_exec(&exec, cmd, pers->mini_env) != 0)
		return (1); // ok avec status_code - seulment des mallocs foireux
	if (exec.total_cmd == 1)
	{
		if (exec.cmd->type == KILLED)
			return (clean_exit_parent(&exec, 0), 0);
		else if (exec.cmd->type == BUILTPAR)
			return (exec_builtin_parent(&exec));
		else
			return (exec_uno(&exec) != 0); // si pb de fork, si argv NULL, si fd ou dup foire et si execve foire.
// ok avec status code ?? / si pas d'erreur retombe en bas et renvoi 0 donc return (fct?)
	}
	else if (exec.total_cmd > 1)
	{
		if (create_pipes(&exec, exec.total_cmd) != 0)
			return (1);
		if (ft_fork(&exec)!= 0)
			return (1); // SI ENFANT KILLED tjr 0 retourne
		clean_end(&exec);
	}
	return (0);
}

 int	initialize_exec(t_exec *exec, t_cmd *cmd, char **mini_env)
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

int	exec_uno(t_exec *exec)
{
	if (exec->cmd->argv == NULL) // pas verifie ds error ? @Corvax, revoir le parsing car prend le infile ou outfile en argv
		return (1);
	if (exec->cmd->type == BUILTPAR)
		return (exec_builtin_parent(exec));
	else
	{
		exec->pid[0] = fork();
		if (exec->pid[0] < 0)
			return (ft_putstr_fd(strerror(errno), 2), 2);
		if (exec->pid[0] == 0)
		{
			if (manage_fds(exec->cmd) != 0)
				return (1);
			if (execve(exec->cmd->path_cmd, exec->cmd->argv, exec->mini_env) == -1)
				return (ft_putstr_fd(strerror(errno), 2), 1); // revoir le message ?
		}
		waitpid(exec->pid[0], NULL, 0);
		clean_exit_parent(exec, 0);
	}
	return (0);
}

int	manage_fds(t_cmd *cmd)
{
	int fdin;
	int fdout;

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
