/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_checks.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:11:31 by ctruchot          #+#    #+#             */
/*   Updated: 2024/03/22 16:04:24 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_CHECKS_H
# define FILE_CHECKS_H

# include "minishell.h"

// typedef struct s_super_cmd
// {
// 	t_cmd	*head_cmd;
// 	int		total_cmd;
// }		t_super_cmd;

// infile_checks.c
int			error_checks(t_cmd *cmd, char **mini_env);
int			check_infiles(t_cmd *cmd, int total_cmd);
int			check_in(t_redirect *in);
int			check_infile_errors(char *path); // ok avec ordre ?
t_redirect	*get_valid_in(t_redirect *in);

// outfile_checks.c
int			check_outfiles(t_cmd *cmd, int total_cmd);
int			check_out(t_redirect *out);
int			create_outfile(t_redirect *out);
t_redirect	*get_valid_out(t_redirect *out);

// here_doc.c
int			get_here_doc(char *path);
void		clean_exit_here_doc(char *lim, int fd);

// cmd_checks.c
int			check_cmd(t_cmd *cmd, int total_cmd, char **env);
char		*get_env(char **env, char *ptr, char *command, t_cmd *cmd);
char		**get_all_paths(char *ptr);
char		*check_paths(char **paths, char *command, t_cmd *cmd);
int			is_valid_path(char *path, char **ptr, char *command);

// utils_in_lists.c
void		print_str_fd(char *s1, char *s2, char *s3, int fd);
int			ft_cmd_lstsize(t_cmd *lst);
t_redirect	*ft_in_lstlast(t_redirect *lst);
void		ft_in_lstclear(t_redirect *lst);
int			free_tab(char **tab);

#endif
