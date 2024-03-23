/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_import.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 19:33:18 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/23 12:47:34 by aduvilla         ###   ########.fr       */
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

void	exec_export(t_exec *exec, t_persistent *pers)
{
	char	**new;
	char	**cpy;

	if (exec->total_cmd != 1)
		exit (1);
	cpy = exec->mini_env;
	new = ft_joinarr(exec->cmd->argv, cpy);
	ft_freetab(cpy);
	if (!new)
		clean_exit_parent(exec, msg_error("minishell:", strerror(errno), 1));
	pers->mini_env = new;
	clean_exit_parent(exec, 0);
}
