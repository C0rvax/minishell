/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:52:09 by ctruchot          #+#    #+#             */
/*   Updated: 2024/03/13 12:23:47 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env_parsing.h"
#include "exec.h"

// int	exec(t_cmd *cmd, char **mini_env)
// {
// 	// int total_cmd;
// 	// // int pid;
	
// 	// total_cmd = ft_cmd_lstsize(cmd);

// 	// if (total_cmd == 1)
// 	// {
// 	// 	pid = fork();
// 	// 	if (pid < 0)
// 	// 		return (ft_putstr_fd(strerror(errno), 2), 2);
// 	// }
// 		exec_uno(cmd, mini_env);
// 	return (0);
// }

int	exec_uno(t_cmd *cmd, char **mini_env)
{
	int fdin;
	int fdout;
	ft_putstr_fd("test", 2);

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

// int	create_pipes(t_struc *data)
// {
// 	int	l;

// 	l = 0;
// 	while (l < data->nbcmd - 1)
// 	{
// 		if (pipe(data->fd[l]) == -1)
// 		{
// 			clean_exit_parent(data, 1);
// 			exit(2);
// 		}
// 		l++;
// 	}
// 	return (0);
// }

// // i is the index of processes and there is one process per command.
// // function forks as many times as number of commands
// // it then enters the childs and parses the files and commands.
// // depending on which child closes the pipes fd

// // i = 0 is the first reading process on the infile and
// // i= nbcmd -1 is the last writing process in the outfile

// int	ft_fork(char **av, char **env, t_struc *data)
// {
// 	while (data->i < data->nbcmd)
// 	{
// 		data->pid[data->i] = fork();
// 		if (data->pid[data->i] < 0)
// 			return (clean_exit_parent(data, 1), 2);
// 		if (data->pid[data->i] == 0)
// 		{
// 			if (parsing(av, env, data) != 0)
// 			{
// 				clean_exit_parent(data, 0);
// 				exit (0);
// 			}
// 			which_process(av, env, data);
// 		}
// 		if (data->i >= 1)
// 		{
// 			close(data->fd[data->i - 1][0]);
// 			close(data->fd[data->i - 1][1]);
// 		}
// 		data->i++;
// 	}
// 	return (0);
// }

// // depending on the i (i.e which command is processed),
// // closes and dup the relevant fd

// void	which_process(char **av, char **env, t_struc *data)
// {
// 	if (data->i == 0)
// 	{
// 		close_higher_fds(data);
// 		if (dup2(data->fd[0][1], STDOUT_FILENO) == -1)
// 			clean_exit_process(data);
// 		close(data->fd[0][1]);
// 		exec_cmd(av, env, data->fdinfile, data);
// 	}
// 	if (data->i > 0 && data->i < data->nbcmd - 1)
// 	{
// 		close_higher_fds(data);
// 		dup_reading_fd(data);
// 		exec_cmd(av, env, data->fd[data->i][1], data);
// 	}
// 	if (data->i == data->nbcmd - 1)
// 	{
// 		dup_reading_fd(data);
// 		exec_cmd(av, env, data->fdoutfile, data);
// 	}
// }

// void	dup_reading_fd(t_struc *data)
// {
// 	close(data->fd[data->i - 1][1]);
// 	if (dup2(data->fd[data->i - 1][0], STDIN_FILENO) == -1)
// 		clean_exit_process(data);
// 	close(data->fd[data->i - 1][0]);
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