/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:22:00 by ctruchot          #+#    #+#             */
/*   Updated: 2024/03/13 18:28:45 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env_parsing.h"
#include "exec.h"
#include "file_checks.h"

int initialize_child(t_child *child, t_exec *exec)
{
	ft_bzero(child, sizeof(t_child));
	child->cmdno = exec->cmdno;
	child->current_cmd = exec->cmd; // attention revoir pour intermediaires
	if (child->cmdno == exec->total_cmd - 1)
		child->current_cmd = ft_cmd_lstlast(exec->cmd);
	ft_printf("cmd=%d\nTEST=%p\n\n", child->cmdno, child->current_cmd);
	ft_putstr_fd(child->current_cmd->path_cmd, 2);
	return (0);
}

int	create_pipes(t_exec *exec, int total_cmd)
{
	int	l;

	l = 0;
	while (l < total_cmd - 1)
	{
		if (pipe(exec->fd[l]) == -1)
		{
			// clean_exit_parent(data, 1); // revoir
			exit(2);
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
			return (2); // clean_exit_parent(exec, 1), 
		if (exec->pid[exec->cmdno] == 0)
		{
			// if (parsing(av, env, exec) != 0)
			// {
			// 	clean_exit_parent(exec, 0);
			// 	exit (0);
			// }
			t_child child;
			initialize_child(&child, exec); // if<<<
			redirect_pipes(exec, &child);
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

// void	close_below_fds(t_exec *exec)
// {
// 	int	l;

// 	l = exec->cmdno - 1;
// 	while (l <= 0)
// 	{
// 		close(exec->fd[l][0]);
// 		close(exec->fd[l][1]);
// 		l--;
// 	}
// }
int manage_fd_firstchild(t_exec *exec, t_child *child)
{
	// int fdout;
	// int fdin;

	// fdout = 0;
	// fdin = 0;
	close_higher_fds(exec);
	if (!exec->cmd->out)
		child->fdout = exec->fd[0][1];
	else
	{
		child->fdout = open(exec->cmd->out->path, O_WRONLY);
		if (child->fdout < 0)
			return (1); // gerer
	}
	if (dup2(child->fdout, STDOUT_FILENO) == -1)
		return (1) ;
		// clean_exit_process(exec);
	close(child->fdout);
	if (exec->cmd->in)
	{
		child->fdin = open(exec->cmd->in->path, O_RDONLY);
		if (child->fdin < 0)
			return (1); // gerer
		if (dup2(child->fdin, STDIN_FILENO) == -1)
			return (1);
			// (/*clean_exit_cmd(exec, arg, fd)*/);
		close (child->fdin);
	}
	// ft_putstr_fd("path=\n", 2);
	// ft_putnbr_fd(child->fdin, 2);
	// ft_putstr_fd(child->current_cmd->path_cmd, 2);
	// ft_putstr_fd("\n\n", 2);

	return (0);
}

int get_fd_files(t_exec *exec, char which)
{
	t_cmd *current_cmd;
	int fd;

	fd = 0;
	current_cmd = ft_cmd_lstlast(exec->cmd);
	if (which == 'i' && current_cmd->in)
	{
		fd = open(current_cmd->in->path, O_RDONLY);
		if (fd < 0)
			return (1); // gerer
		
	}
	if (which == 'o' && current_cmd->out)
	{
		fd = open(current_cmd->out->path, O_WRONLY); // se placer ds le bon cmd
		if (fd < 0)
			return (1); // gerer
	}
	return (fd);
}

int manage_fd_lastchild(t_exec *exec, t_child *child) // faire une cmd get_fd_files
{
	// int fdin;
	// int fdout;

	// fdin = 0;
	// fdout = 0;
	// close_higher_fds(exec); // close lower
	close(exec->fd[exec->cmdno - 1][1]);
	if (!exec->cmd->in)
		child->fdin = exec->fd[exec->cmdno - 1][0];
	else
	{
		child->fdin = get_fd_files(exec, 'i');
		// fdin = open(exec->cmd->in->path, O_RDONLY); // se placer ds le bon cmd
		// if (fdin < 0)
		// 	return (1); // gerer
	}
	if (dup2(child->fdin, STDIN_FILENO) == -1)
		// clean_exit_process(exec);
		return (1);
		// (/*clean_exit_cmd(exec, arg, fd)*/);
	close(child->fdin);
	if (exec->cmd->out)
	{
		child->fdout = get_fd_files(exec, 'o');
		// fdout = open(exec->cmd->out->path, O_WRONLY); // se placer ds le bon cmd
		// if (fdout < 0)
		// 	return (1); // gerer
		if (dup2(child->fdout, STDOUT_FILENO) == -1)
			return (1);
			// (/*clean_exit_cmd(exec, arg, fd)*/);
		close (child->fdout);
	}
	ft_putstr_fd("out=\n", 2);
	ft_putnbr_fd(child->fdout, 2);
	ft_putstr_fd("\n\n", 2);
	ft_putstr_fd(child->current_cmd->path_cmd, 2);
	if (execve(child->current_cmd->path_cmd, child->current_cmd->argv, exec->mini_env) == -1)
		return (1);
	return (0);
}

void	redirect_pipes(t_exec *exec, t_child *child) // redirect pipe
{
	if (exec->cmdno == 0)
	{
		manage_fd_firstchild(exec, child);
		// exec_cmd(exec->fdinfile, exec);
		if (execve(exec->cmd->path_cmd, exec->cmd->argv, exec->mini_env) == -1)
			return;
			//  (/*clean_exit_cmd(exec, arg, fd)*/);
	}
	// if (exec->cmdno > 0 && exec->cmdno < exec->total_cmd - 1)
	// {
	// 	close_higher_fds(exec);
	// 	dup_reading_fd(exec);
	// 	exec_cmd(exec->fd[exec->cmdno][1], exec);
	// }
	if (exec->cmdno == exec->total_cmd - 1)
	{
		manage_fd_lastchild(exec, child);
		
			// (/*clean_exit_cmd(exec, arg, fd)*/);
		// exec_cmd(exec->fdoutfile, exec);
	}
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