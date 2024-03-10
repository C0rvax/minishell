/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:23:28 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/10 02:04:20 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	search_parser_err(t_lst *list)
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

int	parse_read(char *read, char **env)
{
	t_parse	data;

	ft_bzero(&data, sizeof(t_parse));
	if (!read)
		return (1);
	if (create_token_list(&data.lexer, read))
		return (ft_listclear(&data.lexer), 1);
	replace_argument(&data.lexer, env);
	delete_quotes(&data.lexer);
	if (search_errors(data.lexer))
		return (ft_listclear(&data.lexer), 1);
	print_lst(data.lexer);
	ft_listclear(&data.lexer);
	return (0);
}
