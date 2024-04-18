/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 10:55:45 by ctruchot          #+#    #+#             */
/*   Updated: 2024/04/18 17:24:03 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include <sys/wait.h>

typedef struct s_exec
{
	int		total_cmd;
	int		cmdno;
	int		**fd;
	int		*pid;
	t_cmd	*cmd;
	char	**mini_env;
	char	**export;
}			t_exec;

typedef struct s_child
{
	int		fdin;
	int		fdout;
	int		cmdno;
	t_cmd	*current_cmd;
}			t_child;

// exec.c
int			exec(t_cmd *cmd, t_pers *pers);

// exec_multiple_cmd.c
int			create_pipes(t_exec *exec, int total_cmd);
int			ft_fork(t_exec *exec);

// manage_fds.c
void		close_higher_fds(t_exec *exec);
int			manage_fd_firstchild(t_exec *exec, t_child *child);
int			manage_fd_middlechild(t_exec *exec, t_child *child);
int			manage_fd_lastchild(t_exec *exec, t_child *child);

//  clean.c
int			clean_end(t_exec *exec, t_pers *pers);
int			clean_exit_parent(t_exec *exec, int err);
void		clean_exit_child(t_exec *exec, t_child *child, int err);
int			clean_exit_fds(t_exec *exec, t_child *child);
void		close_all_fds(t_exec *exec);

// utils_exec.c
int			free_tab_int(int **fd, int nb);
void		get_status(int status, t_pers *pers);

#endif
