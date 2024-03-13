/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:32:05 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/13 14:39:04 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

int	add_to_history(t_read *list, char *read)
{
	t_read	*new;

	new = ft_read_listnew(read);
	if (!new)
		return (msg_lex(MALLOC, 0, ""), 1);
	ft_read_listadd_back(&list, new);
	return (0);
}
