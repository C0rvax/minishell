/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_parsarray.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:55:00 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/10 18:56:54 by aduvilla         ###   ########.fr       */
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
	int		count;

	buf = lexer;
	count = count_argv(buf);
	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (ft_printf("Error: mallocarg1!\n"), NULL);
	count = 0;
	while (buf && buf->token != PIPE)
	{
		if (buf->next && buf->token != CMD)
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
