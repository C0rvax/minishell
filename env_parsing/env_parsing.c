/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:08:48 by ctruchot          #+#    #+#             */
/*   Updated: 2024/03/22 14:54:15 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_parsing.h"

// t_env	*parse_env_list(char **env)
// {
// 	t_env	*env;
// 	int		i;

// 	i = 0;
// 	env = ft_env_lstnew(env[i]);
// 	if (env == NULL)
// 		return (NULL);
// 	while (env[i + 1])
// 	{
// 		i++;
// 		ft_env_lstadd_back(&env, ft_env_lstnew(env[i]));
// 	}
// 	return (env);
// }

// char	**env_list_to_array(t_env *env)
// {
// 	char	**tab;
// 	int		size;
// 	int		i;

// 	size = 0;
// 	i = 0;
// 	size = ft_env_lstsize(env);
// 	tab = malloc(sizeof(char *) * (size + 1));
// 	if (!tab)
// 		return (NULL);
// 	tab[size] = NULL;
// 	while (env->next != NULL)
// 	{
// 		tab[i] = env->var;
// 		if (!tab[i]) // free le dessus;
// 			return (NULL);
// 		env = env->next;
// 		i++;
// 	}
// 	tab[i] = NULL;
// 	return (tab);
// }

void	parse_env_array(t_persistent *pers, char **env) // necessaire ?
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
		tab[i] = ft_strdup(env[i]);
		i++;
	}
	pers->mini_env = tab;
}

// int	main(int ac, char **av, char **env)
// {
// 	int		i;
// 	t_env	*env;
// 	char	**tab2;
// 	char	**tab;

// 	(void)ac;
// 	(void)av;
// 	i = 0;
// 	// while (env[i])
// 	// {
// 	// 	printf("%s\n", env[i]);
// 	// 	i++;
// 	// }
// 	env = parse_env_list(env);
// 	ft_env(env);
// 	printf("\n\n\n array : \n");
// 	tab2 = env_list_to_array(env);
// 	i = 0;
// 	while (tab2[i] != NULL)
// 	{
// 		printf("%s\n", tab2[i]);
// 		i++;
// 	}
// 	printf("\n\n\n array2 : \n");
// 	tab = parse_env_array(env);
// 	i = 0;
// 	while (tab[i])
// 	{
// 		printf("%s\n", tab[i]);
// 		i++;
// 	}
// 	printf("\n\n\n finish\n");
// 	ft_env_lstclear(env);
// 	free(tab2);
// 	free(tab);
// }
