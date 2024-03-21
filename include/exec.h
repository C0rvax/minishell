/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 10:55:45 by ctruchot          #+#    #+#             */
/*   Updated: 2024/03/21 15:30:01 by ctruchot         ###   ########.fr       */
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

// exec.c

int	exec(t_cmd *cmd, t_persistent *pers);
int initialize_exec(t_exec *exec, t_cmd *cmd, char **mini_env);
int	exec_uno(t_exec *exec);
int	manage_fds(t_cmd *cmd);

// exec2.c

int	create_pipes(t_exec *exec, int total_cmd);
int	ft_fork(t_exec *exec);
int initialize_child(t_child *child, t_exec *exec);
int	redirect_pipes(t_exec *exec, t_child *child);
void	close_higher_fds(t_exec *exec);
int manage_fd_firstchild(t_exec *exec, t_child *child);
int manage_fd_middlechild(t_exec *exec, t_child *child);
int manage_fd_lastchild(t_exec *exec, t_child *child);
void close_all_fds(t_exec *exec);

//  clean.c

void	clean_exit_parent(t_exec *exec, int err);
int	clean_end(t_exec *exec);
int	clean_exit_fds(t_exec *exec, t_child *child);
int	free_tab_int(int **fd, int nb);
void	clean_exit_child(t_exec *exec, int err); // clean exit exec ?



#endif
