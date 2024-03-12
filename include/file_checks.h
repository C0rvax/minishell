/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_checks.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:11:31 by ctruchot          #+#    #+#             */
/*   Updated: 2024/03/12 18:11:42 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_CHECKS_H
# define FILE_CHECKS_H


#include "minishell.h"
#include <fcntl.h>

// infile_checks.c
int	error_checks(t_cmd *cmd);
int	check_infiles(t_cmd *cmd);
int	check_in(t_redirect *in);
int	check_infile_errors(char *path); // ok avec ordre ?
t_redirect *get_valid_in(t_redirect *in);

void kill_child(t_cmd *cmd);

// outfile_checks.c
int	check_outfiles(t_cmd *cmd);
int	check_out(t_redirect *out);
int	check_outfile_errors(char *path);
t_redirect *get_valid_out(t_redirect *out);

// int files_check(t_cmd *cmd);
// int	check_in(t_redirect *in);
// int	check_infile(char *path);
// t_redirect *get_valid_in(t_redirect *in);
// int	check_out(t_redirect *out);
// t_redirect *get_valid_out(t_redirect *out);
void print_str_fd(char *message, char *variable, int fd); //deplacer ailleurs

// here_doc.c
int	get_here_doc(char *path);

// utils_in_lists.c
int	ft_cmd_lstsize(t_cmd *lst);
t_redirect	*ft_in_lstlast(t_redirect *lst);
void	ft_in_lstclear(t_redirect *lst);

#endif


