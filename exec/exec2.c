/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:22:00 by ctruchot          #+#    #+#             */
/*   Updated: 2024/03/19 16:51:14 by ctruchot         ###   ########.fr       */
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
		{
			clean_exit_parent(exec, 1);
			return (1);
		}
		l++;
	}
	return (0);
}

int	ft_fork(t_exec *exec)
{
	while (exec->cmdno < exec->total_cmd)
	{
		exec->pid[exec->cmdno] = fork();
		if (exec->pid[exec->cmdno] < 0)
			return (clean_exit_parent(exec, 1), 2);
		if (exec->pid[exec->cmdno] == 0)
		{
			t_child child;
			if (initialize_child(&child, exec) != 0)
				return (1); // pas de return
			if (redirect_pipes(exec, &child) != 0)
				return (1); // ds quel cas
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

int initialize_child(t_child *child, t_exec *exec)
{
	int i;

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

int	redirect_pipes(t_exec *exec, t_child *child)
{
	if (child->current_cmd->type == KILLED)
		return (1); 
	if (exec->cmdno == 0)
	{
		if (manage_fd_firstchild(exec, child) != 0)
			return (1); // free(child) + clean exec
		exec_builtin(exec, child);
		if (execve(exec->cmd->path_cmd, exec->cmd->argv, exec->mini_env) == -1)
			return (1); // free(child) + clean exec a ce stade ?  
	}
	if (exec->cmdno > 0 && exec->cmdno < exec->total_cmd - 1)
	{
		if (manage_fd_middlechild(exec, child) != 0)
			return (1); // free(child)
		exec_builtin(exec, child);
		if (execve(child->current_cmd->path_cmd, child->current_cmd->argv, exec->mini_env) == -1)
			return (1); // free(child)
	}
	if (exec->cmdno == exec->total_cmd - 1)
	{
		if (manage_fd_lastchild(exec, child) != 0)
			return (1); // free(child)
		exec_builtin(exec, child);
		if (execve(child->current_cmd->path_cmd, child->current_cmd->argv, exec->mini_env) == -1)
			return (1); // free(child)
	}
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
	{
		child->fdout = exec->fd[0][1];
		// ft_putstr_fd("fdoutchild0=\n", 2);
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
	if (child->current_cmd->in)
	{
		child->fdin = open(child->current_cmd->in->path, O_RDONLY);
		// ft_putstr_fd("fdin child0=\n", 2);
		// ft_putnbr_fd(child->fdin, 2);
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
			return (clean_exit_fds(exec, child), 1); // gerer
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

// // depending on the i (i.e which command is processed),
// // closes and dup the relevant fd

// void	which_process(t_exec *exec) // redirect pipe
// {
// 	if (exec->cmdno == 0)
// 	{
// 		close_higher_fds(exec);
// 		if ()
// 		if (exec->cmd->in)
// 		if (dup2(exec->fd[0][1], STDOUT_FILENO) == -1)
// 			clean_exit_process(exec);
// 		close(exec->fd[0][1]);
// 		exec_cmd(exec->fdinfile, exec);
// 	}
// 	if (exec->cmdno > 0 && exec->cmdno < exec->total_cmd - 1)
// 	{
// 		close_higher_fds(exec);
// 		dup_reading_fd(exec);
// 		exec_cmd(exec->fd[exec->cmdno][1], exec);
// 	}
// 	if (exec->cmdno == exec->total_cmd - 1)
// 	{
// 		dup_reading_fd(exec);
// 		exec_cmd(exec->fdoutfile, exec);
// 	}
// }

// void	dup_reading_fd(t_exec *exec)
// {
// 	close(exec->fd[exec->cmdno - 1][1]);
// 	if (dup2(exec->fd[exec->cmdno - 1][0], STDIN_FILENO) == -1)
// 		clean_exit_process(exec);
// 	close(exec->fd[exec->cmdno - 1][0]);
// }

// // depending also on the i, dup the standard in or output
// // and executes the command

// int	exec_cmd(t_cmd *cmd, char **env, int fd,)
// {
// 	if 
// 	int		fdstd;

// 	fdstd = STDOUT_FILENO;
// 	if (data->i == 0)
// 		fdstd = STDIN_FILENO;
	
// 	if (arg == NULL)
// 		return (clean_exit_cmd(data, arg, fd));
// 	if (dup2(fd, fdstd) == -1)
// 		return (clean_exit_cmd(data, arg, fd));
// 	close(fd);
// 	if (execve(data->cmd, arg, env) == -1)
// 		return (clean_exit_cmd(data, arg, fd));
// 	return (0);
// }

// int	exec_cmd(int fd, t_exec *exec)
// {
// 	// int		fdstd;

// 	// fdstd = STDOUT_FILENO;
// 	// if (exec->cmdno == 0)
// 	// 	fdstd = STDIN_FILENO;
// 	if (exec->cmd->in)
// 		if (exec->cmdno = 0)
// 			if (dup2(fdin, STDIN_FILENO) == -1)
// 				return (/*clean_exit_cmd(exec, arg, fd)*/);
// 		else
// 			if (dup2(fdin, exec->fd[exec->cmdno - 1][0]) == -1)
// 				return (/*clean_exit_cmd(exec, arg, fd)*/);	close(fd);
// 	if (exec->cmd->out)
// 		if (exec->cmdno = exec->total_cmd - 1)
// 			if (dup2(fdout, STDOUT_FILENO) == -1)
// 				return (/*clean_exit_cmd(exec, arg, fd)*/);
// 		else
// 			if (dup2(fdout, exec->fd[exec->cmdno][1]) == -1)
// 				return (/*clean_exit_cmd(exec, arg, fd)*/);	close(fd);
	
// 	if (execve(exec->cmd->path_cmd, exec->cmd->argv, exec->mini_env) == -1)
// 		return (/*clean_exit_cmd(exec, arg, fd)*/);
// 	return (0);
// }