/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 19:57:43 by aduvilla          #+#    #+#             */
/*   Updated: 2024/04/02 16:34:59 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char **env, char *str)
{
	char	*value;
	int		i;
	int		len;

	i = 0;
	while (env[i])
	{
		len = ft_strlen(str);
		if (ft_strnstr(env[i], str, len) && env[i][len] == '=')
		{
			value = ft_substr(env[i], len + 1, ft_strlen(env[i]) - (len + 1));
			if (!value)
				return (NULL);
			return (value);
		}
		i++;
	}
	value = malloc(1);
	if (!value)
		return (NULL);
	value[0] = '\0';
	return (value);
}

void	parse_env_array(t_persistent *pers, char **env)
{
	char	**tab;
	int		i;

	i = 0;
	while (env[i])
		i++;
	tab = malloc(sizeof(char *) * (i + 1));
	tab[i] = NULL;
	i = 0;
	while (env[i])
	{
		tab[i] = ft_strdup(env[i]);
		i++;
	}
	pers->mini_env = tab;
}

int	msg_error(char *s1, char *s2, int status)
{
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(s2, 2);
	return (status);
}
