/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clearing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:43:49 by aduvilla          #+#    #+#             */
/*   Updated: 2024/04/04 15:46:32 by aduvilla         ###   ########.fr       */
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

int	msg_built(t_built msg, char *str, int code)
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
	return (code);
}

int	clear_built(t_exec *exec, t_child *child, int code)
{
	(void)child;
	ft_cmd_lstclear(&exec->cmd);
	exec->cmd = NULL;
	close_all_fds(exec);
	free_tab_int(exec->fd, exec->total_cmd - 1);
	if (exec->pid)
		free(exec->pid);
	exec->pid = NULL;
	ft_freetab(exec->mini_env);
	exec->mini_env = NULL;
	ft_freetab(exec->export);
	exec->export = NULL;
	exit (code);
}

int	clear_one(t_exec *exec, int code)
{
	ft_cmd_lstclear(&exec->cmd);
	exec->cmd = NULL;
	close_all_fds(exec);
	free_tab_int(exec->fd, exec->total_cmd - 1);
	if (exec->pid)
		free(exec->pid);
	exec->pid = NULL;
	return (code);
}

int	final_exit(t_exec *exec, t_persistent *pers, int code)
{
	rl_clear_history();
	ft_cmd_lstclear(&exec->cmd);
	exec->cmd = NULL;
	close_all_fds(exec);
	free_tab_int(exec->fd, exec->total_cmd - 1);
	if (exec->pid)
		free(exec->pid);
	exec->pid = NULL;
	ft_freetab(exec->mini_env);
	ft_freetab(pers->export);
	pers->export = NULL;
	exec->mini_env = NULL;
	exit (code);
}
