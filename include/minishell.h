/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:05:34 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/10 14:26:46 by aduvilla         ###   ########.fr       */
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
typedef enum redirect_e
{
	NONE,
	SIMPLE,
	DOUBLE,
}		t_redirect;

/*------- STRUCT -------*/
typedef struct cmd_s
{
	char			**argv;
	t_redirect		in;
	t_redirect		out;
	char			*infile;
	char			*outfile;
	struct cmd_s	*next;
}		t_cmd;

typedef struct data_s
{
	char	**env;
	t_cmd	*cmd;
}		t_data;

/*------- UTILS -------*/

/*------- LIST CMD -------*/
void	print_cmd_lst(t_cmd *cmd);
void	ft_cmd_lstadd_back(t_cmd **list, t_cmd *new);
t_cmd	*ft_cmd_lstlast(t_cmd *list);
t_cmd	*ft_cmd_lstnew(char **argv);
void	ft_cmd_lstclear(t_cmd **cmd);

#endif
