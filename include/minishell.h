/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:05:34 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/10 00:07:48 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*------- LIBRARIES -------*/
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include "libft.h"
# include "ft_printf.h"

/*------- ENUM -------*/

/*------- STRUCT -------*/
typedef struct cmd_s
{
	char			**argv;
	int				in;
	int				out;
	struct cmd_s	*next;
}		t_cmd;

typedef struct data_s
{
	char	**env;
	t_cmd	*cmd;
}		t_data;

/*------- UTILS -------*/
#endif
