/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clearing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:43:49 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/24 10:23:55 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	msg_built2(t_built msg, char *str)
{
	ft_putstr_fd("minishell: ", 2);
	if (msg == PWD)
	{
		ft_putstr_fd("pwd: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
	}
	if (msg == CD)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
	}
	if (msg == HOME)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd("HOME not set\n", 2);
	}
}

int	msg_built(t_built msg, char *str, int status_code)
{
	msg_built2(msg, str);
	if (msg == BMALLOC)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Cannot allocate memory\n", 2);
	}
	if (msg == ARGS)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Too many argument\n", 2);
	}
	if (msg == EXIT)
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
	if (msg == ENV)
	{
		ft_putstr_fd("env: '", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': No such file or directory\n", 2);
	}
	return (status_code);
}

int	clear_built(t_exec *exec, t_child *child, int status_code)
{
	int	i;

	i = 0;
	ft_cmd_lstclear(&exec->cmd);
	exec->cmd = NULL;
	close_all_fds(exec);
	if (exec->fd)
	{
		while (exec->fd[i])
		{
			free(exec->fd[i]);
			i++;
		}
		free(exec->fd);
		exec->fd = NULL;
	}
	if (exec->pid)
		free(exec->pid);
	exec->pid = NULL;
	ft_freetab(exec->mini_env);
	exec->mini_env = NULL;
	exit (status_code);
}

int	clear_one(t_exec *exec, int status_code)
{
	int	i;

	i = 0;
	ft_cmd_lstclear(&exec->cmd);
	exec->cmd = NULL;
	close_all_fds(exec);
	if (exec->fd)
	{
		while (exec->fd[i])
		{
			free(exec->fd[i]);
			i++;
		}
		free(exec->fd);
		exec->fd = NULL;
	}
	if (exec->pid)
		free(exec->pid);
	exec->pid = NULL;
	return (status_code);
}

int	final_exit(t_exec *exec, int status_code)
{
	int	i;

	i = 0;
	rl_clear_history();
	ft_cmd_lstclear(&exec->cmd);
	exec->cmd = NULL;
	close_all_fds(exec);
	if (exec->fd)
	{
		while (exec->fd[i])
		{
			free(exec->fd[i]);
			i++;
		}
		free(exec->fd);
		exec->fd = NULL;
	}
	if (exec->pid)
		free(exec->pid);
	exec->pid = NULL;
	ft_freetab(exec->mini_env);
	exec->mini_env = NULL;
	exit (status_code);
}
