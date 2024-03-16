/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:21:00 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/16 16:16:05 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

/*------- LIBRARIES -------*/
# include "minishell.h"
# include "exec.h"

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
}		t_built;

/*------- CLEARING -------*/
int		clear_built(t_exec *exec, t_child *child, int status_code);
int		msg_built(t_built msg, int status_code);
int		exec_builtin(t_exec *exec, t_child *child);

#endif
