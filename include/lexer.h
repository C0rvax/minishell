/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:46:39 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/09 19:55:43 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <unistd.h>
# include <stdlib.h>
# include "libft.h"
# include "ft_printf.h"

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

typedef struct s_parse
{
	t_lst		*lexer;
}			t_parse;

/*------- LISTS -------*/
t_lst	*ft_listnew(char *str, t_token token);
void	ft_listclear(t_lst **list);
void	ft_listadd_back(t_lst **list, t_lst *new);
void	print_lst(t_lst *lexer);

/*------- UTILS -------*/
int		is_token(char c);
char	*ft_trijoin(char *s1, char *s2, char *s3);

/*------- LEXER -------*/
void	create_token_list(t_lst **lexer, char *read);
int		parse_read(char *read, char **env);
int		replace_argument(t_lst **lexer, char **env);

#endif
