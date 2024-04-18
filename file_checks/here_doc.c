/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:37:48 by ctruchot          #+#    #+#             */
/*   Updated: 2024/04/18 16:09:57 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_checks.h"

// in case of error in get_here_doc

static void	clean_exit_heredoc(char *lim, int fd, int err, t_pers *pers)
{
	if (err == 1)
		ft_putstr_fd(strerror(errno), 2);
	if (err == 2)
	{
		ft_putstr_fd("\nminishell: warning: here-document", 2);
		ft_putstr_fd(" delimited by end-of-file\n", 2);
	}
	pers->status_code = g_status;
	g_status = 0;
	if (lim != NULL)
		free(lim);
	close(fd);
	if (err != 2)
		if (access("/tmp/.tmpheredoc", F_OK) == 0)
			if (unlink("/tmp/.tmpheredoc") != 0)
				ft_putstr_fd(strerror(errno), 2);
}

static int	loop_get_heredoc(char *line, char *lim, int fd, t_pers *pers)
{
	while (ft_strncmp(line, lim, ft_strlen(lim)) != 0)
	{
		ft_putstr_fd(line, fd);
		free(line);
		line = prompted_gnl("> ", 0, 1);
		if (line == NULL && g_status != 130)
			return (clean_exit_heredoc(lim, fd, 2, pers), 0);
		if (g_status == 130 || line == NULL)
			return (clean_exit_heredoc(lim, fd, 0, pers), 1);
	}
	return (free(line), free(lim), close(fd), 0);
}

int	get_here_doc(char *path, t_pers *pers)
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
		return (clean_exit_heredoc(lim, fd, 1, pers), 1);
	line = prompted_gnl("> ", 0, 1);
	if (line == NULL && g_status != 130)
		return (clean_exit_heredoc(lim, fd, 2, pers), 0);
	else if (g_status == 130 || line == NULL)
		return (clean_exit_heredoc(lim, fd, 0, pers), 1);
	return (loop_get_heredoc(line, lim, fd, pers));
}
