/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:00:12 by ctruchot          #+#    #+#             */
/*   Updated: 2024/03/19 15:48:24 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <sys/wait.h> 

int	clean_end(t_exec *exec)
{
	int	j;

	j = exec->total_cmd;
	while (--j >= 0)
		waitpid(exec->pid[j], NULL, 0);
	clean_exit_parent(exec, 0);
	return (0);
}

// to end parent, free all malloc vars and delete the temporary heredoc file

void	clean_exit_parent(t_exec *exec, int err) // clean exit exec ?
{
	if (err == 1)
		ft_putstr_fd(strerror(errno), 2);
	if (exec->fd != NULL)
		free_tab_int(exec->fd, exec->total_cmd - 1);
	if (exec->pid != NULL)
		free(exec->pid);
	if (access(".tmpheredoc", F_OK) == 0)
	{
		if (unlink(".tmpheredoc") != 0)
		{
			ft_putstr_fd(strerror(errno), 2);
		}
	}
}

int	clean_exit_fds(t_exec *exec, t_child *child)
{
	ft_putstr_fd(strerror(errno), 2);
	if (child->cmdno == 0)
	{
		if (child->fdout != 0)
			close(child->fdout);
		else
			close(exec->fd[0][1]);
		if (child->fdin != 0)
			close(child->fdin);
	}
	else if (child->cmdno == exec->total_cmd - 1)
	{
		if (child->fdin != 0)
			close(child->fdin);
		else
			close(exec->fd[child->cmdno - 1][0]);
		if (child->fdout != 0)
			close(child->fdout);
	}
	else
	{
		if (child->fdin != 0)
			close(child->fdin);
		else
			close(exec->fd[child->cmdno - 1][0]);
		if (child->fdout != 0)
			close(child->fdout);
		else
			close(exec->fd[child->cmdno][1]);
	}
	clean_exit_parent(exec, 0);
	// clean_exit_child(child, 0);
	exit(0); // vraiment ?? 
}

int	free_tab_int(int **fd, int nb)
{
	int	i;

	i = 0;
	while (i < nb && fd[i] != NULL)
	{
		free(fd[i]);
		i++;
	}
	free(fd);
	return (0);
}
