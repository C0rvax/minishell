/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 22:43:03 by aduvilla          #+#    #+#             */
/*   Updated: 2024/04/04 18:56:39 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	str_isdigit(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
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

static int	ft_lenarr2(char **argv, char **env)
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
				&& !arg_isok(argv[i]))
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

	new = malloc(sizeof(char *) * (ft_lenarr2(argv, env) + 1));
	if (!new)
		return (NULL);
	i = dup_arr2(&new, env, argv);
	if (i < 0)
		return (ft_freetab(new), NULL);
	j = 1;
	while (argv && argv[j])
	{
		if (ft_strchr(argv[j], '=') == NULL && !arg_isok(argv[j]))
			msg_built(EXPORT, argv[j], 1);
		else if (ft_strchr(argv[j], '=') == NULL)
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
