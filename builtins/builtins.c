/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:48:49 by ctruchot          #+#    #+#             */
/*   Updated: 2024/03/11 15:32:39 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// env with no options or arguments
// env only prints all environment variables

#include "env_parsing.h"

void	ft_exit() // tout cleaner
{
	// ft_printf("exit\n");
	printf("exit\n");

	exit(0);
}

void	ft_env(t_env *node)
{
	while (node != NULL)
	{
		printf("%s\n", node->var); // remplacer par ft_printf
		node = node->next;
	}
}

// void	ft_unset(t_env *node, char *arg) // revoir si l'argument de unset sera envoye comme string 
// + voir si on doit gerer la definition de variables
// {
// 	// if (arg) n'existe pas dans env ou ailleurs si ailleurs doit etre couvert
// }
