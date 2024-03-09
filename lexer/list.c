/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:49:00 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/09 15:22:45 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	ft_listclear(t_lst **list)
{
	t_lst	*buf;

	while (*list)
	{
		buf = (*list)->next;
		free((*list)->str);
		free(*list);
		*list = buf;
	}
	free((*list)->str);
	free(*list);
	*list = NULL;
}

t_lst	*ft_listnew(char *str, t_token token)
{
	t_lst	*new;

	new = malloc(sizeof(t_lst) * 1);
	if (!new)
		return (NULL);
	new->str = ft_strdup(str);
	if (!new->str)
		return (free(new), NULL);
	new->token = token;
	new->next = NULL;
	return (new);
}

t_lst	*ft_listlast(t_lst *list)
{
	if (!list)
		return (NULL);
	while (list->next != NULL)
		list = list->next;
	return (list);
}

void	ft_listadd_back(t_lst **list, t_lst *new)
{
	t_lst	*buf;

	if (!list || !new)
		return ;
	if (*list == NULL)
		*list = new;
	else
	{
		buf = ft_listlast(*(list));
		buf->next = new;
	}
}
