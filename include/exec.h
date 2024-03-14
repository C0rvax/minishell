/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 10:55:45 by ctruchot          #+#    #+#             */
/*   Updated: 2024/03/14 13:03:28 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

#include "minishell.h"

typedef struct s_exec
{
	int		total_cmd;
	int		cmdno;
	int		**fd;
	int		*pid;
	t_cmd	*cmd;
	char **mini_env;
	// int		fdinfile;
	// int		fdoutfile;
}			t_exec;

typedef struct s_child
{
	int		fdin;
	int		fdout;
	int		cmdno;
	t_cmd	*current_cmd;
}			t_child;

int	exec(t_cmd *cmd, char **mini_env);
int initialize_exec(t_exec *exec, t_cmd *cmd, char **mini_env);

int	exec_uno(t_cmd *cmd, char **mini_env);
int	create_pipes(t_exec *exec, int total_cmd);
int	ft_fork(t_exec *exec);
void	close_higher_fds(t_exec *exec);
int manage_fd_firstchild(t_exec *exec, t_child *child);
int manage_fd_lastchild(t_exec *exec, t_child *child);// faire une cmd get_fd_files
void	redirect_pipes(t_exec *exec, t_child *child); // redirect pipe

#endif
