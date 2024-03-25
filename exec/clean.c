/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:00:12 by ctruchot          #+#    #+#             */
/*   Updated: 2024/03/25 19:13:21 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <sys/wait.h> 

int	clean_end(t_exec *exec, t_persistent *pers)
{
	int	j;
	int	status;
	int	status_code;

	status_code = 0;
	j = 0;
	while (j < exec->total_cmd)
	{
		waitpid(exec->pid[j], &status, 0);
		if (WIFEXITED(status))
		{
			if (exec->cmd->code_err == 127)
				pers->status_code = 127;
			else
				pers->status_code = WEXITSTATUS(status);
		}	
		j++;
		exec->cmd = exec->cmd->next;
	}
	clean_exit_parent(exec, 0);
	return (pers->status_code);
}

// to end parent, free all malloc vars and delete the temporary heredoc file

int	clean_exit_parent(t_exec *exec, int err) 
{
	if (err == 1)
		ft_putstr_fd(strerror(errno), 2);
	if (exec->fd != NULL)
		free_tab_int(exec->fd, exec->total_cmd - 1);
	if (exec->pid != NULL)
	{
		free(exec->pid);
		exec->pid = NULL;
	}
	if (access(".tmpheredoc", F_OK) == 0)
	{
		if (unlink(".tmpheredoc") != 0)
			ft_putstr_fd(strerror(errno), 2);
	}
	ft_cmd_lstclear(&exec->cmd);
	return (err); // @status code
}

void	clean_exit_child(t_exec *exec, int err)
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
	if (exec->mini_env != NULL)
		ft_freetab(exec->mini_env);
	ft_cmd_lstclear(&exec->cmd);
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
	// clean_exit_parent(exec, 0);
	clean_exit_child(exec, 0);
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
	fd = NULL;
	return (0);
}

// close pas fdin et fdout ????
void close_all_fds(t_exec *exec)
{
	int	l;

	l = 0;
	while (l < exec->total_cmd - 1)
	{
		if (exec->fd[l][0] >= 0)
			close(exec->fd[l][0]);
		if (exec->fd[l][1] >= 0)
		close(exec->fd[l][1]);
		l++;
	}
	if (access(".tmpheredoc", F_OK) == 0)
	{
		if (unlink(".tmpheredoc") != 0)
			ft_putstr_fd(strerror(errno), 2);
	}
}
