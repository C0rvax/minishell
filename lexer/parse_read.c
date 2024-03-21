/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:23:28 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/21 16:05:45 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

t_cmd	*parse_read(char *read, char **env)
{
	t_parse	parse;

	ft_bzero(&parse, sizeof(t_parse));
	if (!read || read[0] == '\0')
		return (NULL);
	if (check_read(&read))
		return (NULL);
	if (create_token_list(&parse.lexer, read))
		return (ft_listclear(&parse.lexer), NULL);
	if (replace_argument(&parse.lexer, env))
		return (ft_listclear(&parse.lexer), NULL);
	delete_quotes(&parse.lexer);
	if (search_errors(parse.lexer))
		return (ft_listclear(&parse.lexer), NULL);
	if (create_cmd_list(&parse))
		return (ft_listclear(&parse.lexer), ft_cmd_lstclear(&parse.cmd), NULL);
	ft_listclear(&parse.lexer);
	add_history(read);
	return (parse.cmd);
}
/*
ft_cmd_lstclear(&parse.cmd);
*/
