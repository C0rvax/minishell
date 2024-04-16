/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 12:44:24 by aduvilla          #+#    #+#             */
/*   Updated: 2024/04/16 16:12:38 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	is_in_env(char **tab, char *str)
{
	int		i;
	char	*var;

	i = 0;
	if (!tab || !str)
		return (0);
	var = ft_strjoin(str, "=");
	if (!var)
		return (-1);
	while (tab[i])
	{
		if (!ft_strncmp(tab[i], var, ft_strlen(var)))
			return (free(var), 1);
		i++;
	}
	return (free(var), 0);
}

static int	count_in_env(char **env, char **argv)
{
	int		i;
	int		in;
	int		count;

	i = 1;
	count = 0;
	if (argv && argv[0])
	{
		while (argv[i])
		{
			in = is_in_env(env, argv[i]);
			if (in < 0)
				return (-1);
			if (in == 1)
				count++;
			i++;
		}
	}
	return (count);
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
			return (-1);
		if (!ft_strncmp(str, var, ft_strlen(var)))
			return (free(var), 1);
		free(var);
		i++;
	}
	return (0);
}

static int	copy_unset(char ***new, char **env, char **argv)
{
	int		i;
	int		u;
	int		count;

	i = 0;
	count = 0;
	while (env[i + count])
	{
		u = is_unset(env[i + count], argv);
		if (u < 0)
			return (1);
		if (u == 0)
		{
			new[0][i] = ft_strdup(env[i + count]);
			if (!new[0][i])
				return (1);
			i++;
		}
		else
			count++;
	}
	new[0][i] = NULL;
	return (0);
}

int	exec_unset(t_exec *exec, t_pers *pers)
{
	char	**cpy;
	char	**argv;
	char	**new;
	int		count;

	cpy = pers->mini_env;
	argv = exec->cmd->argv;
	count = count_in_env(cpy, argv);
	if (count < 0)
		return (clear_one(exec, msg_built(BMALLOC, argv[1], 1)));
	new = malloc(sizeof(char *) * (ft_lenarr(cpy, NULL) - count + 1));
	if (!new)
		return (clear_one(exec, msg_built(BMALLOC, argv[1], 1)));
	if (copy_unset(&new, cpy, argv))
	{
		ft_freetab(new);
		return (clear_one(exec, msg_built(BMALLOC, argv[1], 1)));
	}
	ft_freetab(cpy);
	pers->mini_env = new;
	if (unset_exp(exec, pers))
		return (1);
	return (clear_one(exec, 0));
}
