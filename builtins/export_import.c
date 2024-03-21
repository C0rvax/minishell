/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_import.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 19:33:18 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/21 17:30:09 by aduvilla         ###   ########.fr       */
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
		while(arr[i])
		{
			res++;
			i++;
		}
		return (res);
	}
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

	i = ft_lenarr(exp, 0);
	j = ft_lenarr(env, 1);
	if (!i)
		return (NULL);
	new = malloc(sizeof(char *) * (i + j + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (env && env[++i])
		new[i] = ft_strdup(env[i]);
	j = -1;
	while (exp && exp[++j])
	{
		if (ft_strchr(exp[j], '=') != NULL)
			new[i++] = ft_strdup(exp[j]);
	}
	new[i] = NULL;
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

void	exec_export(t_exec *exec)
{
	char	**new;
	char	**cpy;

	if (exec->total_cmd != 1)
		exit (1);
	cpy = exec->mini_env;
	new = ft_joinarr(exec->cmd->argv, cpy);
	ft_freetab(cpy);
	if (!new)
		exit (1);
	exec->mini_env = new;
	clean_exit_parent(exec, 0);
}

void	exec_unset(t_exec *exec)
{
	char	**cpy;
	int		i;
	int		count;

	i = 1;
	count = 0;
	cpy = exec->mini_env;
	while (exec->cmd->argv[i])
	{
		if (str_in_arr(cpy, exec->cmd->argv[i]))
			count++;
	}
}
