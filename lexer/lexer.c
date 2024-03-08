/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:00:25 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/08 16:01:08 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	istok(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	else
		return (0);
}

void	create_list_node(t_list *list, char *read, int *i, int *j)
{
	t_list	*new;

	if (read[*i] == '|')
	if (*i > 0 && read[*i - 1] != '<' && read[*i - 1] != '>')
	{
		new = ft_lstnew(ft_substr(read, *j, *i - *j));
		ft_lstadd_back(&list, new);
		new = ft_lstnew(read[*i]);
		ft_lstadd_back(&list, new);
	}
}
int	count_token(char *read)
{
	int	i;
	int	count;

	count = 0;
	if (read)
	{
		while(read[i])
		{
			if (read && read[i] == 39)
			{
				i++;
				while (read[i] && read[i] != 39)
					i++;
			}
			if (read[i] && read[i] == 34)
			{
				i++;
				while (read[i] && read[i] != 34)
					i++;
			}
			if (read[i] && istok(read[i]))
				create_list_node(read, &i, &j);
			if (read[i] && read[i] == '|')
				count += 2;
			if (read[i] && read[i] == ' ')
				count += 1;
			if (read[i] && read[i] == '<')
			{
				if (i > 0 && read[i - 1] != '<')
					count += 2;
			}
			if (read[i] && read[i] == '>')
			{
				if (i > 0 && read[i - 1] != '>')
					count += 2;
			}
		}
	}
}

