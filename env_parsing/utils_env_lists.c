/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lists.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:44:07 by ctruchot          #+#    #+#             */
/*   Updated: 2024/03/11 15:29:02 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_parsing.h"

t_env	*ft_env_lstnew(char *var)
{
	t_env	*new;

	new = NULL;
	new = malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->var = var;
	new->next = NULL;
	return (new);
}

t_env	*ft_env_lstlast(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	ft_env_lstadd_back(t_env **lst, t_env *new)
{
	if (!lst || !new)
		return (1);
	if ((*lst) == NULL)
		*lst = new;
	else
		ft_env_lstlast(*lst)->next = new;
	return (0);
}

t_env	*ft_env_lstalmostlast(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next->next)
		lst = lst->next;
	return (lst);
}

int	ft_env_lstsize(t_env *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}
