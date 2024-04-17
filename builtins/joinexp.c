/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joinexp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:27:51 by aduvilla          #+#    #+#             */
/*   Updated: 2024/04/17 14:32:03 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	is_inarg2(char **argv, char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (argv[i])
	{
		if (!ft_strcmp(str, argv[i]))
			count++;
		i++;
	}
	if (count > 1)
		return (1);
	else
		return (0);
}

static int	is_inenv2(char *str, char **env)
{
	int		i;

	i = 0;
	if (!env | !str)
		return (0);
	while (env[i])
	{
		if (!ft_strcmp(env[i], str))
			return (1);
		i++;
	}
	return (0);
}

static int	dup_arr2(char ***new, char **env, char **argv)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (env && env[i + count])
	{
		if (is_inenv2(env[i + count], argv))
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

static int	lenarr_exp(char **argv, char **env)
{
	int	i;
	int	res;

	i = 1;
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
			if (!ft_strchr(argv[i], '=') && !is_inenv2(argv[i], env)
				&& !is_inarg2(&argv[i], argv[i]) && !arg_isok(argv[i]))
				res++;
			i++;
		}
	}
	return (res);
}

char	**ft_joinexp(char **argv, char **env)
{
	int		i;
	int		j;
	char	**new;

	new = malloc(sizeof(char *) * (lenarr_exp(argv, env) + 1));
	if (!new)
		return (NULL);
	i = dup_arr2(&new, env, argv);
	if (i < 0)
		return (ft_freetab(new), NULL);
	j = 1;
	while (argv && argv[j])
	{
		if (!ft_strchr(argv[j], '=') && arg_isok(argv[j]))
			msg_built(EXPORT, argv[j], 1);
		else if (!ft_strchr(argv[j], '=') && !is_inarg2(&argv[j], argv[j]))
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
