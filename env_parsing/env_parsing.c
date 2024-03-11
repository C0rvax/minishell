/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:08:48 by ctruchot          #+#    #+#             */
/*   Updated: 2024/03/11 15:37:51 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_parsing.h"

t_env	*parse_env_list(char **env)
{
	t_env	*node;
	int		i;

	i = 0;
	node = ft_env_lstnew(env[i]);
	if (node == NULL)
		return (NULL);
	while (env[i + 1])
	{
		i++;
		ft_env_lstadd_back(&node, ft_env_lstnew(env[i]));
	}
	return (node);
}

char	**env_list_to_array(t_env *node)
{
	char	**tab;
	int		size;
	int		i;

	size = 0;
	i = 0;
	size = ft_env_lstsize(node);
	tab = malloc(sizeof(char *) * (size + 1));
	if (!tab)
		return (NULL);
	tab[size] = NULL;
	while (node->next != NULL)
	{
		tab[i] = node->var;
		if (!tab[i]) // free le dessus;
			return (NULL);
		node = node->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

char	**parse_env_array(char **env) // necessaire ?
{
	char	**tab;
	int		i;

	i = 0;
	while (env[i])
		i++;
	tab = malloc(sizeof(char *) * (i + 1));
	tab[i] = NULL;
	i = 0;
	while (env[i])
	{
		// tab[i] = ft_strdup(env[i]);
		tab[i] = env[i];
		i++;
	}
	return (tab);
}

int	main(int ac, char **av, char **env)
{
	int		i;
	t_env	*node;
	char	**tab2;
	char	**tab;

	(void)ac;
	(void)av;
	i = 0;
	// while (env[i])
	// {
	// 	printf("%s\n", env[i]);
	// 	i++;
	// }
	node = parse_env_list(env);
	ft_env(node);
	printf("\n\n\n array : \n");
	tab2 = env_list_to_array(node);
	i = 0;
	while (tab2[i] != NULL)
	{
		printf("%s\n", tab2[i]);
		i++;
	}
	printf("\n\n\n array2 : \n");
	tab = parse_env_array(env);
	i = 0;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
	printf("\n\n\n finish\n");
	ft_env_lstclear(node);
	free(tab2);
	free(tab);
}
