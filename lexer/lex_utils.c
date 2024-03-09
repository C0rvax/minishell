/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:45:30 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/09 20:42:11 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	is_token(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == ' ' || c == '$')
		return (1);
	else
		return (0);
}

char	*ft_trijoin(char *s1, char *s2, char *s3)
{
	char	*cpy;
	char	*join;

	join = ft_strjoin(s1, s2);
	if (!join)
		return (free(s1), free(s2), free(s3), NULL);
	cpy = join;
	join = ft_strjoin(cpy, s3);
	free(cpy);
	free(s1);
	free(s2);
	free(s3);
	if (!join)
		return (NULL);
	return (join);
}
