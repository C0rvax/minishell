/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_import.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 19:33:18 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/22 14:01:26 by aduvilla         ###   ########.fr       */
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

char	**ft_joinarr(char **exp, char **env)
{
	int		i;
	int		j;
	char	**new;

	new = malloc(sizeof(char *) * (ft_lenarr(exp, 0) + ft_lenarr(env, 1) + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (env && env[++i])
	{
		new[i] = ft_strdup(env[i]);
		if (!new[i])
			return (ft_freetab(new), NULL);
	}
	j = -1;
	while (exp && exp[++j])
	{
		if (ft_strchr(exp[j], '=') != NULL)
		{
			new[i++] = ft_strdup(exp[j]);
			if (!new[i])
				return (ft_freetab(new), NULL);
		}
	}
	new[i] = NULL;
	return (new);
}
//proteger les dup !

int	str_in_arr(char **tab, char *str)
{
	int	i;

	i = 0;
	if (!tab || !str)
		return (0);
	while (tab[i])
	{
		if (ft_strncmp(tab[i], str, ft_strlen(tab[i])))
			return (1);
	}
	return (0);
}

void	exec_export(t_exec *exec, t_persistent *pers)
{
	char	**new;
	char	**cpy;

	if (exec->total_cmd != 1)
		exit (1);
	cpy = pers->mini_env;
	ft_printf("===========================================================\n");
	ft_printf("===========================================================\n");
	ft_putar(pers->mini_env);
	ft_printf("===========================================================\n");
	ft_printf("===========================================================\n");
	new = ft_joinarr(exec->cmd->argv, cpy);
	ft_freetab(cpy);
	if (!new)
		clean_exit_parent (exec, msg_error("minishell:", strerror(errno), 1));
//	exec->mini_env = new;
	pers->mini_env = new;
	ft_printf("avant crash\n");
	ft_putar(pers->mini_env);
	ft_printf("apres crash\n");
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
