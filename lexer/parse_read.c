/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:23:28 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/29 17:43:21 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

extern int g_status_code;

static void	exit_parse(char **env, char *read)
{
	free(read);
	ft_freetab(env);
	rl_clear_history();
	exit (0);
}

static int	append_new_read(char **read, t_persistent *pers)
{
	char	*cpy;
	char	*read2;
	int		i;

	if (search_errors(*read))
		return (free(*read), 1);
	i = ft_strlen(read[0]);
	while (i > 0 && read[0][i - 1] == '|')
	{
		read2 = readline("> ");
		if (!read2)
			exit_parse(pers->mini_env, *read);
		cpy = read[0];
		*read = ft_strjoin(cpy, read2);
		free(cpy);
		free(read2);
		if (!*read)
			return (msg_lex(MALLOC, 0, ""), 1);
		if (search_errors(*read))
			return (free(*read), 1);
		i = ft_strlen(read[0]);
	}
	return (0);
}

t_cmd	*parse_read(char *read, t_persistent *pers)
{
	t_parse	parse;

	ft_bzero(&parse, sizeof(t_parse));
	if (!read || read[0] == '\0')
		return (NULL);
	if (append_new_read(&read, pers))
		return (NULL);
	add_history(read);
	if (create_token_list(&parse.lexer, read))
		return (ft_listclear(&parse.lexer), NULL);
	if (replace_argument(&parse.lexer, pers))
		return (ft_listclear(&parse.lexer), NULL);
	if (delete_quotes(&parse.lexer))
		return (ft_listclear(&parse.lexer), NULL);
	if (create_cmd_list(&parse))
		return (ft_listclear(&parse.lexer), ft_cmd_lstclear(&parse.cmd), NULL);
	ft_listclear(&parse.lexer);
	return (parse.cmd);
}
