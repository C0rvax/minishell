/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 00:08:43 by aduvilla          #+#    #+#             */
/*   Updated: 2024/04/18 16:23:41 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	delete_char(t_lst *list, char c, int *index)
{
	int		count;
	int		i;
	char	*cpy;

	i = 0;
	count = 0;
	cpy = list->str;
	list->str = malloc(sizeof(char) * (ft_strlen(cpy) - 1));
	if (!list->str)
		return (msg_lex(MALLOC, 0, ""), 1);
	while (cpy[i + count])
	{
		if (cpy[i + count] == c && count < 2 && i >= *index)
		{
			count++;
			*index = i;
		}
		else
		{
			list->str[i] = cpy[i + count];
			i++;
		}
	}
	list->str[i] = '\0';
	return (free(cpy), 0);
}

int	delete_quotes(t_lst **list)
{
	t_lst	*buf;
	int		i;
	int		status_code1;
	int		status_code2;

	buf = *list;
	status_code1 = 0;
	status_code2 = 0;
	while (buf)
	{
		i = 0;
		while (buf->str[i])
		{
			if (buf->str[i] == 39)
				status_code1 = delete_char(buf, 39, &i);
			if (buf->str[i] == 34)
				status_code2 = delete_char(buf, 34, &i);
			if (status_code1 || status_code2)
				return (1);
			if (buf->str[i] && buf->str[i] != 39 && buf->str[i] != 34)
				i++;
		}
		buf = buf->next;
	}
	return (0);
}
