/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 19:33:18 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/24 10:30:43 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_lenarr(char **arr, int mode)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	if (!arr)
		return (0);
	if (mode == 1)
	{
		while (arr[i])
			i++;
		return (i);
	}
	while (arr[i])
	{
		if (arr[i] && ft_strchr(arr[i], '=') != NULL)
			res++;
		i++;
	}
	return (res);
}

static int	dup_arr(char ***new, char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		new[0][i] = ft_strdup(env[i]);
		if (!new[0][i])
			return (ft_freetab(*new), -1);
		i++;
	}
	return (i);
}

static char	**ft_joinarr(char **exp, char **env)
{
	int		i;
	int		j;
	char	**new;

	new = malloc(sizeof(char *) * (ft_lenarr(exp, 0) + ft_lenarr(env, 1) + 1));
	if (!new)
		return (NULL);
	i = dup_arr(&new, env);
	if (i < 0)
		return (ft_freetab(new), NULL);
	j = 0;
	while (exp && exp[j])
	{
		if (ft_strchr(exp[j], '=') != NULL)
		{
			new[i++] = ft_strdup(exp[j]);
			if (!new[i - 1])
				return (ft_freetab(new), NULL);
		}
		j++;
	}
	new[i] = NULL;
	return (new);
}

int	exec_export(t_exec *exec, t_persistent *pers)
{
	char	**new;
	char	**argv;
	char	**cpy;

	if (exec->total_cmd != 1)
		return (clear_one(exec, 0));
	argv = exec->cmd->argv;
	cpy = exec->mini_env;
	new = ft_joinarr(argv, cpy);
	if (!new)
		return (clear_one(exec, msg_built(BMALLOC, argv[1], 1)));
	ft_freetab(cpy);
	pers->mini_env = new;
	return (clear_one(exec, 0));
}
