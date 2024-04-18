/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:21:00 by aduvilla          #+#    #+#             */
/*   Updated: 2024/04/18 14:51:33 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

/*------- LIBRARIES -------*/
# include "exec.h"
# include "minishell.h"

typedef enum e_built
{
	BMALLOC,
	HOME,
	CD,
	PWD,
	ENV,
	EXIT,
	ARGS,
	FD,
	EXPORT
}		t_built;

/*------- CLEARING -------*/
int		clear_built(t_exec *exec, t_child *child, int status_code);
int		clear_one(t_exec *exec, int status_code);
int		msg_built(t_built msg, char *str, int status_code);
int		final_exit(t_exec *exec, t_pers *pers, int status_code);
void	print_str_fd(char *s1, char *s2, char *s3, int fd);

/*------- MAIN -------*/
int		is_a_builtin(t_cmd *cmd);
int		exec_builtin(t_exec *exec, t_child *child);
int		exec_builtin_parent(t_exec *exec, t_pers *pers);

/*------- UTILS -------*/
int		ft_lenarr(char **argv, char **env);
int		redirect_out(t_exec *exec);
char	**ft_joinarr(char **argv, char **env);
char	**ft_joinexp(char **argv, char **env);
int		arg_isok(char *str);
int		print_export(t_exec *exec, int mode);

/*------- EXEC -------*/
void	exec_export_c(t_exec *exec, t_child *child);
void	exec_unset_c(t_exec *exec, t_child *child);
void	exec_echo_c(t_exec *exec, t_child *child);
void	exec_cd_c(t_exec *exec, t_child *child);
void	exec_pwd_c(t_exec *exec, t_child *child);
void	exec_env_c(t_exec *exec, t_child *child);
void	exec_exit_c(t_exec *exec, t_child *child);
int		unset_exp(t_exec *exec, t_pers *pers);

/*------- EXEC PARENT -------*/
int		exec_export(t_exec *exec, t_pers *pers);
int		exec_unset(t_exec *exec, t_pers *pers);
int		exec_cd(t_exec *exec, t_pers *pers);
int		exec_pwd(t_exec *exec);
int		exec_env(t_exec *exec);
int		exec_echo(t_exec *exec);
void	exec_exit_parent(t_exec *exec, t_pers *pers);
#endif
