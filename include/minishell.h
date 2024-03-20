/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:05:34 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/20 20:11:29 by aduvilla         ###   ########.fr       */
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
# include "get_next_line.h"

/*------- ENUM -------*/
typedef enum e_mode
{
	SIMPLE,
	DOUBLE
}		t_mode;

typedef enum e_type
{
	COMMAND,
	KILLED,
	BUILTPAR,
	BUILTCHILD
}		t_type;

/*------- STRUCT -------*/
typedef struct s_redirect
{
	t_mode				mode;
	char				*path;
	struct s_redirect	*next;
}		t_redirect;

typedef struct s_cmd
{
	char			**argv;
	char			*path_cmd;
	t_redirect		*in;
	t_redirect		*out;
	t_type			type;
	struct s_cmd	*next;
}		t_cmd;

typedef struct s_read
{
	char			*read;
	struct s_read	*next;
}		t_read;

typedef struct s_data
{
	char	**env;
	t_cmd	*cmd;
}		t_data;

typedef struct s_persistent
{
	char	**mini_env;
	int		status_code;
}		t_persistent;

/*------- UTILS -------*/
int		add_to_history(t_read *list, char *read);
char	*ft_getenv(char **env, char *str);
char	*get_prompt(char **env);

/*------- LIST CMD -------*/
void	print_cmd_lst(t_cmd *cmd);
void	ft_cmd_lstadd_back(t_cmd **list, t_cmd *new);
t_cmd	*ft_cmd_lstlast(t_cmd *list);
t_cmd	*ft_cmd_lstnew(char **argv);
void	ft_cmd_lstclear(t_cmd **cmd);

/*------- LIST READ -------*/
void	ft_read_listclear(t_read **list);
t_read	*ft_read_listnew(char *str);
t_read	*ft_read_listlast(t_read *list);
void	ft_read_listadd_back(t_read **list, t_read *new);
void	print_read_lst(t_read *list);

/*------- LIST REIDRECT -------*/
void		ft_redir_listclear(t_redirect **list);
t_redirect	*ft_redir_listnew(char *str, t_mode mode);
t_redirect	*ft_redir_listlast(t_redirect *list);
void		ft_redir_listadd_back(t_redirect **list, t_redirect *new);
void		print_redir_lst(t_redirect *list);

#endif
