/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:37:48 by ctruchot          #+#    #+#             */
/*   Updated: 2024/04/04 15:47:01 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_checks.h"

// in case of error in get_here_doc

void	clean_exit_here_doc(char *lim, int fd, int err)
{
	if (err == 1)
		ft_putstr_fd(strerror(errno), 2);
	if (lim != NULL)
		free(lim);
	close(fd);
	if (access(".tmpheredoc", F_OK) == 0)
	{
		if (unlink(".tmpheredoc") != 0)
		{
			ft_putstr_fd(strerror(errno), 2);
		}
	}
}

int	get_here_doc(char *path)
{
	char	*lim;
	char	*line;
	int		fd;

	lim = NULL;
	line = NULL;
	lim = ft_strjoin(path, "\n");
	if (lim == NULL)
		return (ft_putstr_fd(strerror(errno), 2), 1);
	fd = open(".tmpheredoc", O_RDWR | O_TRUNC | O_CREAT, 0777);
	if (fd == -1)
		return (clean_exit_here_doc(lim, fd, 1), 1);
	line = get_next_line(0);
	if (line == NULL)
		return (clean_exit_here_doc(lim, fd, 0), 1);
	while (ft_strncmp(line, lim, ft_strlen(lim)) != 0)
	{
		ft_putstr_fd(line, fd);
		free(line);
		line = get_next_line(0);
		if (line == NULL)
			return (clean_exit_here_doc(lim, fd, 0), 1);
	}
	return (free(line), free(lim), close(fd), 0);
}
/*
int	get_here_doc(char *path)
{
	char	*line;
	int		fd;

	line = NULL;
	fd = open(".tmpheredoc", O_RDWR | O_TRUNC | O_CREAT, 0777);
	if (fd == -1)
		return (clean_exit_here_doc(fd), 1);
	line = get_next_line(0);
	if (line == NULL)
		return (clean_exit_here_doc(fd), 1);
	while (ft_strncmp(line, path, ft_strlen(line)) != 0)
	{
		ft_putstr_fd(line, fd);
		free(line);
		line = get_next_line(0);
		if (line == NULL)
			return (clean_exit_here_doc(fd), 1);
	}
	return (free(line), close(fd), 0);
}
*/
