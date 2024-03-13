/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:37:48 by ctruchot          #+#    #+#             */
/*   Updated: 2024/03/12 22:30:00 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_checks.h"

// prevoir de unlink le fichier temp

int	get_here_doc(char *path)
{
	char	*lim;
	char	*line;
	int		fd;

	lim = NULL;
	line = NULL;
	lim = ft_strjoin(path, "\n");
	if (lim == NULL)
		exit(2);
	fd = open(".tmpheredoc", O_RDWR | O_TRUNC | O_CREAT, 0777);
	if (fd == -1)
		return (clean_exit_here_doc(lim, fd), 1);
	line = get_next_line(0);
	if (line == NULL)
		return (clean_exit_here_doc(lim, fd), 1);
	while (ft_strncmp(line, lim, ft_strlen(lim)) != 0)
	{
		ft_putstr_fd(line, fd);
		free(line);
		line = get_next_line(0);
		if (line == NULL)
			return (clean_exit_here_doc(lim, fd), 1);
	}
	return (free(line), free(lim), close(fd), 0);
}

// in case of error in get_here_doc

void	clean_exit_here_doc(char *lim, int fd)
{
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

void	kill_child(t_cmd *cmd)
{
	if (cmd->argv != NULL) // confirmer
	{
		free(cmd->argv = NULL);
		cmd->argv = NULL;
	}
	if (cmd->in != NULL)
	{
		free(cmd->in = NULL);
		cmd->in = NULL;
	}
	if (cmd->out != NULL)
	{
		free(cmd->out = NULL);
		cmd->out = NULL;
	}
}
