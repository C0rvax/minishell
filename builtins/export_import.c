/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_import.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 19:33:18 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/22 16:03:34 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	ft_lenarr(char **arr, int mode)
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

static char	**ft_joinarr(char **exp, char **env)
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
			if (!new[i - 1])
				return (ft_freetab(new), NULL);
		}
	}
	new[i] = NULL;
	return (new);
}

static int	is_in_env(char **tab, char *str)
{
	int		i;
	char	*var;

	i = 0;
	if (!tab || !str)
		return (0);
	var = ft_strjoin(str, "=");
	if (!var)
		return (0);
	while (tab[i])
	{
		if (ft_strncmp(tab[i], var, ft_strlen(var)))
			return (free(var), 1);
	}
	return (free(var), 0);
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

static int	is_unset(char *str, char **tab)
{
	int		i;
	char	*var;

	i = 1;
	if (!tab || !str)
		return (0);
	while (tab[i])
	{
		var = ft_strjoin(tab[i], "=");
		if (!var)
			return (0);
		if (ft_strncmp(str, var, ft_strlen(var)))
			return (free(var), 1);
		free(var);
		i++;
	}
	return (0);
}

void	exec_unset(t_exec *exec, t_persistent *pers)
{
	char	**cpy;
	char	**new;
	int		i;
	int		count;

	i = 0;
	count = 0;
	cpy = pers->mini_env;
	while (exec->cmd->argv[++i])
	{
		if (is_in_env(cpy, exec->cmd->argv[i]))
			count++;
	}
	ft_printf("count : %d\n", count);
	new = malloc(sizeof(char *) * (ft_lenarr(cpy, 1) - count + 1));
	if (!new)
		clean_exit_parent(exec, msg_error("minishell:", strerror(errno), 1));
	i = 0;
	count = 0;
	while (cpy[i + count])
	{
		if (!is_unset(cpy[i + count], exec->cmd->argv))
		{
			ft_printf("on print la ligne\n");
			new[i] = ft_strdup(cpy[i + count]);
			if (!new[i])
				clean_exit_parent(exec,
					  msg_error("minishell:", strerror(errno), 1));
			i++;
		}
		else
			count++;
	}
	new[i] = NULL;
	ft_freetab(cpy);
	pers->mini_env = new;
}
