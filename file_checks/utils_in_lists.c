/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_in_lists.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:14:49 by ctruchot          #+#    #+#             */
/*   Updated: 2024/03/12 12:01:20 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_checks.h"

int	ft_cmd_lstsize(t_cmd *lst) // necessaire de proteger ?
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

t_redirect	*ft_in_lstlast(t_redirect *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_in_lstclear(t_redirect *lst)
{
	t_redirect	*buff;

	if (!lst)
		return;
	while(lst->next)
	{
		buff = lst->next;
		// free(lst->mode); // revoir si necessaire
		free(lst->path);
		free(lst);
		lst = buff;
	}
}
	
// 	t_redirect	*almostlast;

// 	last = NULL;
// 	almostlast = NULL;
// 	if (lst == NULL)
// 		return ;
// 	while (lst->next != NULL)
// 	{
// 		last = ft_in_lstlast(lst);
// 		almostlast = ft_in_lstalmostlast(lst);
// 		almostlast->next = NULL;
// 		// free(last);
// 		free
// 	}
// 	free(lst);
// 	return ;
// }

// t_redirect	*ft_in_lstalmostlast(t_redirect *lst)
// {
// 	if (!lst)
// 		return (NULL);
// 	while (lst->next->next)
// 		lst = lst->next;
// 	return (lst);
// }