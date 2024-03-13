/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:23:28 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/13 11:10:02 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

t_cmd	*parse_read(char *read, char **env)
{
	t_parse	parse;

	ft_bzero(&parse, sizeof(t_parse));
	if (!read)
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
	print_lst(parse.lexer);
	print_cmd_lst(parse.cmd);
	ft_listclear(&parse.lexer);
	free(read);
	return (parse.cmd);
}
