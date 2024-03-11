/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 13:04:58 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/10 13:06:50 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	search_parser_err(t_lst *list)
{
	t_lst	*buf;

	buf = list;
	while (buf)
	{
		if (buf->token != CMD && buf->token != PIPE)
		{
			if (buf->next == NULL || buf->next->token != CMD)
				return (ft_printf("bash: syntax error near unexpected tok"), 1);
		}
		buf = buf->next;
	}
	return (0);
}

int	search_errors(t_lst *list)
{
	if (search_parser_err(list))
		return (1);
	return (0);
}
