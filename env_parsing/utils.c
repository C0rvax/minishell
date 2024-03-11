/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:55:56 by ctruchot          #+#    #+#             */
/*   Updated: 2024/03/11 15:36:55 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_parsing.h"

int	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (0);
}

int	free_tab_int(int **fd, int nb)
{
	int	i;

	i = 0;
	while (i < nb && fd[i] != NULL)
	{
		free(fd[i]);
		i++;
	}
	free(fd);
	return (0);
}

void	ft_env_lstclear(t_env *node)
{
	t_env	*last;
	t_env	*almostlast;

	last = NULL;
	almostlast = NULL;
	if (node == NULL)
		return ;
	while (node->next != NULL)
	{
		last = ft_env_lstlast(node);
		almostlast = ft_env_lstalmostlast(node);
		almostlast->next = NULL;
		free(last);
	}
	free(node);
	return ;
}
