/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:46:39 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/08 15:51:53 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <unistd.h>

typedef enum token_e
{
	CMD,
	PIPE,
	IN,
	DIN,
	OUT,
	DOUT
}			t_token;

typedef struct s_list
{
	char			*str;
	t_token			token;
	struct s_list	*next;
}			t_list;

#endif
