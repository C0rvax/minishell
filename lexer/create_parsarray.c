/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_parsarray.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:55:00 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/12 16:00:42 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static char	**malloc_argv(t_lst *lexer)
{
	int		i;
	t_lst	*buf;
	char	**argv;

	buf = lexer;
	argv = NULL;
	i = 0;
	while (buf && buf->token != PIPE)
	{
		if (buf->token == CMD)
			i++;
		if (buf->token != CMD)
			i--;
		buf = buf->next;
	}
	if (i == 0)
	{
		argv = malloc(sizeof(char *) * 1);
		argv[0] = NULL;
	}
	else
		argv = malloc(sizeof(char *) * (i + 1));
	if (!argv)
		return (msg_lex(MALLOC, 0, ""), NULL);
	return (argv);
}

char	**create_arg_array(t_lst *lexer)
{
	t_lst	*buf;
	char	**argv;
	int		count;

	buf = lexer;
	argv = malloc_argv(buf);
	if (!argv || argv[0] == NULL)
		return (argv);
	count = 0;
	while (buf && buf->token != PIPE)
	{
		if (buf->next && buf->token != CMD && buf->next->token != PIPE)
			buf = buf->next->next;
		else
		{
			argv[count] = ft_strdup(buf->str);
			if (!argv[count])
				return (ft_freetab(argv), ft_printf("Error: malloc2\n"), NULL);
			count++;
			buf = buf->next;
		}
	}
	argv[count] = NULL;
	return (argv);
}
