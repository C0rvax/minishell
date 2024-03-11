/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:23:28 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/10 19:18:03 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

int	parse_read(char *read, char **env)
{
	t_parse	parse;

	ft_bzero(&parse, sizeof(t_parse));
	if (!read)
		return (1);
	if (create_token_list(&parse.lexer, read))
		return (ft_listclear(&parse.lexer), 1);
	replace_argument(&parse.lexer, env);
	delete_quotes(&parse.lexer);
	if (search_errors(parse.lexer))
		return (ft_listclear(&parse.lexer), 1);
	create_cmd_list(&parse);
	print_cmd_lst(parse.cmd);
	print_lst(parse.lexer);
	ft_cmd_lstclear(&parse.cmd);
	ft_listclear(&parse.lexer);
	return (0);
}
