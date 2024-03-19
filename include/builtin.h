/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:21:00 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/19 17:18:59 by ctruchot         ###   ########.fr       */
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
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
}	t_built;

/*------- CLEARING -------*/
int	clear_built(t_exec *exec, t_child *child, int status_code);
int	msg_built(t_built msg, int status_code);
int	exec_builtin(t_exec *exec, t_child *child);
int	final_exit(t_exec *exec, int status_code);

int	is_a_builtin(t_cmd *cmd);
int	exec_builtin_par(t_exec *exec);

#endif
