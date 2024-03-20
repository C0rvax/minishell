/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_import.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 19:33:18 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/20 19:40:10 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_lenarr(char **arr)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	if (!arr)
		return (0);
	while (arr[i])
	{
		if (arr[i] && ft_strchr(arr[i], '=') != NULL)
			res++;
		i++;
	}
	return (res);
}

char	**ft_joinarr(char **exp, char **env)
{
	int		i;
	int		j;
	char	**new;

	i = ft_lenarr(exp);
	j = ft_lenarr(env);
	if (!i)
		return (NULL);
	new = malloc(sizeof(char *) * (i + j + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (env && env[++i])
		new[i] = env[i];
	j = 0;
	while (exp[j])
	{
		if (ft_strchr(exp[j], '=') != NULL)
			new[i + j] = exp[j];
		j++;
	}
	new[i + j] = NULL;
	return (new);
}

int	str_in_arr(char **tab, char *str)
{
	int	i;

	i = 0;
	if (!tab || !str)
		return (0);
	while (tab[i])
	{
		if (ft_strncmp(tab[i], str, ft_strlen(str)))
			return (1);
	}
	return (0);
}

void	exec_export(t_exec *exec, t_child *child)
{
	char	**new;
	char	**cpy;

	if (exec->total_cmd != 1)
		clear_built(exec, child, 0);
	cpy = exec->mini_env;
	new = ft_joinarr(child->current_cmd->argv, cpy);
	ft_freetab(cpy);
	if (!new)
		clear_built(exec, child, 0);
	exec->mini_env = new;
}

void	exec_unset(t_exec *exec, t_child *child)
{
	char	**cpy;
	int		i;
	int		count;

	i = 1;
	count = 0;
	cpy = exec->mini_env;
	while (child->current_cmd->argv[i])
	{
		if (str_in_arr(cpy, child->current_cmd->argv[i]))
			count++;
	}
}
