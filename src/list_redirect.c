/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:16:39 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/11 15:28:58 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redir_listclear(t_redirect **list)
{
	t_redirect	*buf;

	while ((*list)->next)
	{
		buf = (*list)->next;
		free((*list)->path);
		free(*list);
		*list = buf;
	}
	free((*list)->path);
	free(*list);
	*list = NULL;
}

t_redirect	*ft_redir_listnew(char *str, t_mode mode)
{
	t_redirect	*new;

	new = malloc(sizeof(t_redirect) * 1);
	if (!new)
		return (NULL);
	new->path = str;
	if (!new->path)
		return (free(new), NULL);
	new->mode = mode;
	new->next = NULL;
	return (new);
}

t_redirect	*ft_redir_listlast(t_redirect *list)
{
	if (!list)
		return (NULL);
	while (list->next != NULL)
		list = list->next;
	return (list);
}

void	ft_redir_listadd_back(t_redirect **list, t_redirect *new)
{
	t_redirect	*buf;

	if (!list || !new)
		return ;
	if (*list == NULL)
		*list = new;
	else
	{
		buf = ft_redir_listlast(*(list));
		buf->next = new;
	}
}

void	print_redir_lst(t_redirect *list)
{
	int	i;

	i = 0;
	if (list)
	{
		while (list)
		{
			ft_printf("path[%d] = %s\n", i, list->path);
			if (list->mode == SIMPLE)
				ft_printf("mode : simple\n");
			if (list->mode == DOUBLE)
				ft_printf("mode : double\n");
			list = list->next;
			i++;
		}
	}
}
