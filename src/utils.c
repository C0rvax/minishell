/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 19:57:43 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/20 19:59:08 by aduvilla         ###   ########.fr       */
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
		if (ft_strnstr(env[i], str, len))
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
