/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:10:00 by aduvilla          #+#    #+#             */
/*   Updated: 2024/04/17 15:23:53 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	no_loop(char *str, int i)
{
	int	j;

	j = i;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (!ft_strncmp(str, &str[i + 1], j - 1))
				return (1);
		}
		i++;
	}
	return (0);
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
	if (str && str[i] == '=')
	{
		if (no_loop(str, i))
			return (1);
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
			if (argv[i] && ft_strchr(argv[i], '=') && !arg_isok(argv[i]))
				res++;
			i++;
		}
	}
	return (res);
}

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
