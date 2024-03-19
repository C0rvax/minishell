/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:37:48 by ctruchot          #+#    #+#             */
/*   Updated: 2024/03/19 11:58:13 by ctruchot         ###   ########.fr       */
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
		return (ft_putstr_fd(strerror(errno), 2), 1);
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
		free_tab(cmd->argv);
		cmd->argv = NULL;
	}
	if (cmd->in != NULL)
	{
		ft_in_lstclear(cmd->in);
		cmd->in = NULL;
	}
	if (cmd->out != NULL)
	{
		ft_in_lstclear(cmd->out);
		cmd->out = NULL;
	}
	if (cmd->path_cmd != NULL)
	{
		free(cmd->path_cmd);
		cmd->path_cmd = NULL;
	}
	cmd->type = KILLED;
}
