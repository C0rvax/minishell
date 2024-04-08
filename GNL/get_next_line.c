/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:56:26 by ctruchot          #+#    #+#             */
/*   Updated: 2024/04/08 14:12:26 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "minishell.h"

char	*gnl_cleanstash(char *stash, unsigned int start, size_t len)
{
	char			*temp;
	size_t			j;
	unsigned int	mem;

	if (!stash)
		return (NULL);
	if (start > len)
		return (NULL);
	mem = len - start + 1;
	temp = malloc(sizeof(char) * mem);
	if (!temp)
		return (NULL);
	gnl_bzero(temp, mem);
	j = 0;
	if (stash[start])
	{
		while (stash[start])
		{
			temp[j] = stash[start];
			j++;
			start++;
		}
	}
	temp[j] = '\0';
	return (temp);
}

int	gnl_isline(char *s)
{
	int	i;

	i = 0;
	if (s[0] == 0)
		return (0);
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*gnl_getline(char *s, size_t lineend)
{
	char	*line;
	size_t	i;

	i = 0;
	if (s[lineend] == '\n')
		lineend = lineend + 1;
	line = malloc(sizeof(char) * (lineend + 1));
	if (!line)
		return (NULL);
	while (s[i] && i < lineend)
	{
		line[i] = s[i];
		i++;
	}
	line[lineend] = '\0';
	if (line[0] == '\0')
		return (free(line), line = NULL, NULL);
	return (line);
}

char	*gnl_read(int fd, char *stash)
{
	char	*buffer;
	int		r;

	r = 1;
	buffer = NULL;
	signals(3);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (r > 0)
	{
		r = read(fd, buffer, BUFFER_SIZE);
		if (r == 0)
			return (free(buffer), stash);
		if (r < 0 || g_status == 130)
			return (free(stash), free(buffer), NULL);
		buffer[r] = '\0';
		stash = update_stash(stash, buffer);
		if (!stash)
			return (NULL);
		if (gnl_isline(buffer) == 1)
			break ;
	}
	return (free(buffer), stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	int			i;
	char		*stv1;

	i = 0;
	if ((fd < 0) || (read(fd, 0, 0) != 0) || (BUFFER_SIZE <= 0))
		return (free(stash), stash = NULL, NULL);
	if (!stash)
		stash = gnl_mallocstash(stash);
	if (!stash)
		return (NULL);
	stash = gnl_read(fd, stash);
	while (stash && stash[i] != '\0' && stash[i] != '\n')
		i++;
	if (stash && (stash[i] == '\n' || stash[i] == '\0'))
	{
		line = gnl_getline(stash, i);
		stv1 = stash;
		stash = gnl_cleanstash(stash, i + 1, gnl_strlen(stash));
		if (!stash)
			return (free(stv1), stv1 = NULL, line);
		return (free(stv1), stv1 = NULL, free(stash), stash = NULL, line);
	}
	return (free(stash), NULL);
}
