/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:00:12 by ctruchot          #+#    #+#             */
/*   Updated: 2024/04/02 15:01:46 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

int	clean_end(t_exec *exec)
{
	int		j;
	int		status;
	t_cmd	*buf;

	j = 0;
	buf = exec->cmd;
	while (j < exec->total_cmd)
	{
		waitpid(exec->pid[j], &status, 0);
		if (WIFEXITED(status))
		{
			if (buf->code_err == 127)
				g_status = 127;
			else if (buf->code_err == 126)
				g_status = 126;
			else
				g_status = WEXITSTATUS(status);
		}
		j++;
		buf = buf->next;
	}
	clean_exit_parent(exec, 0);
	return (g_status);
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
	return (err);
}

void	clean_exit_child(t_exec *exec, t_child *child, int err)
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
	if (child->current_cmd->code_err == 127)
	{
		ft_cmd_lstclear(&exec->cmd);
		exit(127);
	}
	ft_cmd_lstclear(&exec->cmd);
	exit(1);
}

int	clean_exit_fds(t_exec *exec, t_child *child)
{
	ft_putstr_fd(strerror(errno), 2);
	if (child->fdout > 0)
		close(child->fdout);
	if (child->fdin > 0)
		close(child->fdin);
	clean_exit_child(exec, child, 0);
	exit(1);
}

// close pas fdin et fdout ????

void	close_all_fds(t_exec *exec)
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
