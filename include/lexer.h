/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:46:39 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/14 16:10:05 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>
# include "minishell.h"

/*------- ENUM -------*/
typedef enum token_e
{
	CMD,
	PIPE,
	IN,
	DIN,
	OUT,
	DOUT
}			t_token;

/*------- STRUCT -------*/
typedef struct s_lst
{
	char			*str;
	t_token			token;
	struct s_lst	*next;
}			t_lst;

typedef enum e_msg
{
	SPECIAL,
	TOKEN,
	QUOTE,
	MALLOC
}			t_msg;

typedef struct s_parse
{
	t_lst		*lexer;
	t_cmd		*cmd;
}			t_parse;

/*------- LISTS -------*/
t_lst	*ft_listnew(char *str, t_token token);
void	ft_listclear(t_lst **list);
void	ft_listadd_back(t_lst **list, t_lst *new);
void	print_lst(t_lst *lexer);

/*------- MAIN TOOLS -------*/
char	*get_prompt(void);

/*------- UTILS -------*/
int		is_token(char c);
char	*ft_trijoin(char *s1, char *s2, char *s3);
int		pass_quote(char *str, int *i);
void	pass_simple_quote(char *str, int *i);
int		is_special(char c);

/*------- ERRORS -------*/
int		search_errors(t_lst *list);
void	msg_lex(t_msg msg, char c, char *str);
int		check_read(char **read);

/*------- LEXER -------*/
int		create_token_list(t_lst **lexer, char *read);
t_cmd	*parse_read(char *read, char **env);
int		replace_argument(t_lst **lexer, char **env);
int		delete_quotes(t_lst **list);

/*------- PARSER -------*/
int		create_cmd_list(t_parse *parse);
char	**create_arg_array(t_lst *lexer);

#endif
