/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:45:30 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/28 20:09:26 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	is_token(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	else
		return (0);
}

int	is_special(char c)
{
	if (c == '&' || c == '*' || c == ';' || c == '@' || c == '^' || c == '#'
		|| c == '!' || c == '\\')
		return (1);
	else
		return (0);
}

char	*ft_trijoin(char *s1, char *s2, char *s3)
{
	char	*firstjoin;
	char	*join;

	firstjoin = ft_strjoin(s1, s2);
	if (!firstjoin)
		return (free(s1), free(s2), free(s3), NULL);
	join = ft_strjoin(firstjoin, s3);
	free(firstjoin);
	free(s1);
	free(s2);
	free(s3);
	return (join);
}

void	pass_simple_quote(char *str, int *i)
{
	if (str[*i] && str[*i] == 39)
	{
		*i = *i + 1;
		while (str[*i] && str[*i] != 39)
			*i = *i + 1;
	}
}

int	pass_quote(char *str, int *i)
{
	int	j;

	if (str[*i] && str[*i] == 39)
	{
		j = *i;
		*i = *i + 1;
		while (str[*i] && str[*i] != 39)
			*i = *i + 1;
		if (str[*i] == '\0')
			return (msg_lex(QUOTE, '\0', &str[j]), 1);
	}
	if (str[*i] && str[*i] == 34)
	{
		j = *i;
		*i = *i + 1;
		while (str[*i] && str[*i] != 34)
			*i = *i + 1;
		if (str[*i] == '\0')
			return (msg_lex(DQUOTE, '\0', &str[j]), 1);
	}
	return (0);
}
