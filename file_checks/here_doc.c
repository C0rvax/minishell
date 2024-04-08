/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:37:48 by ctruchot          #+#    #+#             */
/*   Updated: 2024/04/08 15:48:28 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_checks.h"

// in case of error in get_here_doc

void	clean_exit_here_doc(char *lim, int fd, int err)
{
	if (err == 1)
		ft_putstr_fd(strerror(errno), 2);
	if (err == 2)
	{
		ft_putstr_fd("minishell: warning: here-document", 2);
		ft_putstr_fd(" delimited by end-of-file\n", 2);
	}
	if (lim != NULL)
		free(lim);
	close(fd);
	if (err != 2)
		if (access("/tmp/.tmpheredoc", F_OK) == 0)
			if (unlink("/tmp/.tmpheredoc") != 0)
				ft_putstr_fd(strerror(errno), 2);
}

int	loop_get_here_doc(char *line, char *lim, int fd)
{
	while (ft_strncmp(line, lim, ft_strlen(lim)) != 0)
	{
		ft_putstr_fd(line, fd);
		free(line);
		line = get_next_line(0);
		if (line == NULL && g_status != 130)
			return (clean_exit_here_doc(lim, fd, 2), 0);
		if (g_status == 130 || line == NULL)
			return (clean_exit_here_doc(lim, fd, 0), 1);
	}
	return (free(line), free(lim), close(fd), 0);
}

int	get_here_doc(char *path)
{
	char	*lim;
	char	*line;
	int		fd;

	line = NULL;
	lim = ft_strjoin(path, "\n");
	if (lim == NULL)
		return (ft_putstr_fd(strerror(errno), 2), 1);
	fd = open("/tmp/.tmpheredoc", O_RDWR | O_TRUNC | O_CREAT, 0777);
	if (fd == -1)
		return (clean_exit_here_doc(lim, fd, 1), 1);
	line = get_next_line(0);
	if (line == NULL && g_status != 130)
		return (clean_exit_here_doc(lim, fd, 2), 0);
	else if (g_status == 130 || line == NULL)
		return (clean_exit_here_doc(lim, fd, 0), 1);
	return (loop_get_here_doc(line, lim, fd));
}
