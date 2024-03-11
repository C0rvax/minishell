/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:05:34 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/11 17:22:48 by aduvilla         ###   ########.fr       */
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
typedef enum mode_e
{
	SIMPLE,
	DOUBLE,
}		t_mode;

/*------- STRUCT -------*/
typedef struct redirect_s
{
	t_mode				mode;
	char				*path;
	struct redirect_s	*next;
}		t_redirect;

typedef struct cmd_s
{
	char			**argv;
	t_redirect		*in;
	t_redirect		*out;
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

/*------- LIST REIDRECT -------*/
void		ft_redir_listclear(t_redirect **list);
t_redirect	*ft_redir_listnew(char *str, t_mode mode);
t_redirect	*ft_redir_listlast(t_redirect *list);
void		ft_redir_listadd_back(t_redirect **list, t_redirect *new);
void		print_redir_lst(t_redirect *list);

#endif
