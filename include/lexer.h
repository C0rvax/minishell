/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:46:39 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/08 18:06:34 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

typedef enum token_e
{
	CMD,
	PIPE,
	IN,
	DIN,
	OUT,
	DOUT
}			t_token;

typedef struct s_lst
{
	char			*str;
	t_token			token;
	struct s_lst	*next;
}			t_lst;

t_lst	*ft_listnew(char *str, t_token token);
void	ft_listclear(t_lst **list);
void	ft_listadd_back(t_lst **list, t_lst *new);

#endif
