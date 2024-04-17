/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joinarr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:30:12 by aduvilla          #+#    #+#             */
/*   Updated: 2024/04/17 14:32:58 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	is_inarg(char **argv, char *str)
{
	int		i;
	int		j;
	int		count;
	char	*ptr;

	i = 0;
	count = 0;
	ptr = ft_strchr(str, '=');
	if (ptr)
	{
		j = ft_strlen(str) - ft_strlen(ptr);
		while (argv[i])
		{
			if (!ft_strncmp(str, argv[i], j + 1))
				count++;
			i++;
		}
	}
	if (count > 1)
		return (1);
	else
		return (0);
}

static int	is_inenv(char *str, char **env)
{
	int		i;
	int		j;
	char	*ptr;

	i = 0;
	if (!env | !str)
		return (0);
	while (env[i])
	{
		ptr = ft_strchr(env[i], '=');
		if (ptr)
		{
			j = ft_strlen(env[i]) - ft_strlen(ptr);
			if (!ft_strncmp(env[i], str, j + 1))
				return (1);
		}
		i++;
	}
	return (0);
}

static int	lenarr_env(char **argv, char **env)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	if (env)
	{
		while (env[res])
			res++;
	}
	if (argv)
	{
		while (argv[i])
		{
			if (argv[i] && ft_strchr(argv[i], '=') && !is_inenv(argv[i], env)
				&& !is_inarg(&argv[i], argv[i]) && !arg_isok(argv[i]))
				res++;
			i++;
		}
	}
	return (res);
}

static int	dup_arr(char ***new, char **env, char **argv)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (env && env[i + count])
	{
		if (is_inenv(env[i + count], argv))
			count++;
		else
		{
			new[0][i] = ft_strdup(env[i + count]);
			if (!new[0][i])
				return (ft_freetab(*new), -1);
			i++;
		}
	}
	return (i);
}

char	**ft_joinarr(char **argv, char **env)
{
	int		i;
	int		j;
	char	**new;

	new = malloc(sizeof(char *) * (lenarr_env(argv, env) + 1));
	if (!new)
		return (NULL);
	i = dup_arr(&new, env, argv);
	if (i < 0)
		return (ft_freetab(new), NULL);
	j = 0;
	while (argv && argv[j])
	{
		if (ft_strchr(argv[j], '=') && arg_isok(argv[j]))
			msg_built(EXPORT, argv[j], 1);
		else if (ft_strchr(argv[j], '=') && !is_inarg(&argv[j], argv[j]))
		{
			new[i++] = ft_strdup(argv[j]);
			if (!new[i - 1])
				return (ft_freetab(new), NULL);
		}
		j++;
	}
	new[i] = NULL;
	return (new);
}
