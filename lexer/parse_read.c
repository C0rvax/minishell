/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:23:28 by aduvilla          #+#    #+#             */
/*   Updated: 2024/04/18 15:20:07 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

static void	sig_parse(void)
{
	struct sigaction	parsig;

	sigemptyset(&parsig.sa_mask);
	parsig.sa_handler = &handle_sigint_read;
	parsig.sa_flags = 0;
	sigaction(SIGINT, &parsig, NULL);
}

t_cmd	*parse_read(char *read, t_pers *pers)
{
	t_parse	parse;

	sig_parse();
	ft_bzero(&parse, sizeof(t_parse));
	if (!read || read[0] == '\0')
		return (NULL);
	if (append_new_read(&read, pers))
		return (NULL);
	add_history(read);
	if (replace_argument(&read, pers))
		return (free(read), ft_listclear(&parse.lexer), NULL);
	if (create_token_list(&parse.lexer, read))
		return (free(read), ft_listclear(&parse.lexer), NULL);
	free(read);
	if (delete_quotes(&parse.lexer))
		return (ft_listclear(&parse.lexer), NULL);
	if (create_cmd_list(&parse))
		return (ft_listclear(&parse.lexer), ft_cmd_lstclear(&parse.cmd), NULL);
	ft_listclear(&parse.lexer);
	if (parse.cmd == NULL)
		pers->status_code = -1;
	return (parse.cmd);
}
