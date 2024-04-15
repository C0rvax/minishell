/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:10:00 by aduvilla          #+#    #+#             */
/*   Updated: 2024/04/15 14:38:26 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

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

int	arg_isok(char *str)
{
	int	i;

	i = 0;
	if (str && str[i] != '_' && !ft_isalpha(str[i]))
		return (1);
	while (str && str[i] != '\0' && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	ft_lenarr(char **argv, char **env)
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
				&& !arg_isok(argv[i]))
				res++;
			i++;
		}
	}
	return (res);
}

char	**ft_joinarr(char **argv, char **env)
{
	int		i;
	int		j;
	char	**new;

	new = malloc(sizeof(char *) * (ft_lenarr(argv, env) + 1));
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
		else if (ft_strchr(argv[j], '=') != NULL)
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
