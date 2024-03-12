/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 00:08:43 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/12 18:38:46 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	count_char(char *str, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

static void	delete_char(t_lst *list, char c)
{
	int		count;
	int		i;
	char	*new;
	char	*cpy;

	i = 0;
	count = count_char(list->str, c);
	new = malloc(sizeof(char) * (ft_strlen(list->str) - count + 1));
	if (!new)
		exit (1);
	count = 0;
	while (list->str[i + count])
	{
		if (list->str[i + count] == c)
			count++;
		else
		{
			new[i] = list->str[i + count];
			i++;
		}
	}
	new[i] = '\0';
	cpy = list->str;
	list->str = new;
	free(cpy);
}

int	delete_quotes(t_lst **list)
{
	t_lst	*buf;
	int		i;

	buf = *list;
	while (buf)
	{
		i = 0;
		while (buf->str[i])
		{
			if (buf->str[i] == 39)
			{
				delete_char(buf, 39);
				break ;
			}
			if (buf->str[i] == 34)
			{
				delete_char(buf, 34);
				break ;
			}
			i++;
		}
		buf = buf->next;
	}
	return (0);
}
