/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_parsarray.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:55:00 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/23 13:55:17 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	count_argv(t_lst *lexer)
{
	int		i;
	t_lst	*buf;

	buf = lexer;
	i = 0;
	while (buf && buf->token != PIPE)
	{
		if (buf->token == CMD)
			i++;
		if (buf->token != CMD)
			i--;
		buf = buf->next;
	}
	return (i);
}

char	**create_arg_array(t_lst *lexer)
{
	t_lst	*buf;
	char	**argv;
	int		i;

	buf = lexer;
	argv = malloc(sizeof(char *) * (count_argv(buf) + 1));
	if (!argv)
		return (msg_lex(MALLOC, 0, ""), NULL);
	i = 0;
	while (buf && buf->token != PIPE && count_argv(buf) > 0)
	{
		if (buf->next && buf->token != CMD && buf->next->token != PIPE)
			buf = buf->next->next;
		else
		{
			argv[i] = ft_strdup(buf->str);
			if (!argv[i])
				return (ft_freetab(argv), msg_lex(MALLOC, 0, ""), NULL);
			i++;
			buf = buf->next;
		}
	}
	argv[i] = NULL;
	return (argv);
}
