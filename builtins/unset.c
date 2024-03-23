/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 12:44:24 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/23 13:58:35 by aduvilla         ###   ########.fr       */
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
		return (0);
	while (tab[i])
	{
		if (ft_strncmp(tab[i], var, ft_strlen(var)))
			return (free(var), 1);
	}
	return (free(var), 0);
}

static int	count_in_env(char **env, char **argv)
{
	int		i;
	int		count;

	i = 1;
	count = 0;
	if (argv && argv[0])
	{
		while (argv[i])
		{
			if (is_in_env(env, argv[i]))
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
			return (0);
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
	int		count;

	i = 0;
	count = 0;
	while (env[i + count])
	{
		if (!is_unset(env[i + count], argv))
		{
			new[0][i] = ft_strdup(env[i + count]);
			if (!new[0][i])
				return (msg_error("minishell:", strerror(errno), 1));
			i++;
		}
		else
			count++;
	}
	new[0][i] = NULL;
	return (0);
}

void	exec_unset(t_exec *exec, t_persistent *pers)
{
	char	**cpy;
	char	**new;
	int		count;

	cpy = pers->mini_env;
	count = count_in_env(cpy, exec->cmd->argv);
	new = malloc(sizeof(char *) * (ft_lenarr(cpy, 1) - count + 1));
	if (!new)
		clean_exit_parent(exec, msg_error("minishell:", strerror(errno), 1));
	if (copy_unset(&new, cpy, exec->cmd->argv))
		clean_exit_parent(exec, 1);
	ft_freetab(cpy);
	pers->mini_env = new;
	clean_exit_parent(exec, 0);
}
