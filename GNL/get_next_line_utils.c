/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:48:30 by ctruchot          #+#    #+#             */
/*   Updated: 2024/01/31 17:27:03 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*s3;
	size_t	i;
	size_t	j;
	size_t	mem;

	if (!s1 || !s2)
		return (NULL);
	mem = gnl_strlen(s1) + gnl_strlen(s2) + 1;
	s3 = malloc(sizeof(char) * mem);
	if (!s3)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		s3[i + j] = s2[j];
		j++;
	}
	s3[i + j] = 0;
	return (s3);
}

char	*gnl_mallocstash(char *stash)
{
	stash = malloc(1);
	if (!stash)
		return (NULL);
	stash[0] = '\0';
	return (stash);
}

void	gnl_bzero(void *s, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		((unsigned char *)s)[i] = 0;
		i++;
	}
}
