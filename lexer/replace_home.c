/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_home.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:33:34 by aduvilla          #+#    #+#             */
/*   Updated: 2024/04/15 18:21:37 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

int	replace_home(t_pers *pers, char **read, int index)
{
	char	*arg;
	char	*value;
	char	c;

	c = read[0][index + 1];
	if (c == '\0' || c == ' ' || c == '/')
	{
		arg = "";
		value = ft_getenv(pers->mini_env, "HOME");
		if (!value)
			return (msg_lex(MALLOC, 0, ""), 1);
		if (value[0])
		{
			if (replace_in_list(read, arg, value, index))
				return (1);
		}
	}
	return (0);
}
