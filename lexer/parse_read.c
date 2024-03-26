/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:23:28 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/26 14:19:15 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

static void	exit_parse(char **env)
{
	ft_freetab(env);
	rl_clear_history();
	exit (0);
}

t_cmd	*parse_read(char *read, t_persistent *pers)
{
	t_parse	parse;
	int		red;

	ft_bzero(&parse, sizeof(t_parse));
	if (!read || read[0] == '\0')
		return (NULL);
	red = check_read(&read);
	if (red == 2)
		exit_parse(pers->mini_env);
	if (red == 1)
		return (NULL);
	if (create_token_list(&parse.lexer, read))
		return (ft_listclear(&parse.lexer), NULL);
	if (replace_argument(&parse.lexer, pers))
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
