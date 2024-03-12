/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:37:48 by ctruchot          #+#    #+#             */
/*   Updated: 2024/03/12 11:28:49 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_checks.h"

int	get_here_doc(char *path) // prevoir de unlink le fichier temp
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
		return (1); // ajouter function type clean_exit_here_doc(lim, fd)
	line = get_next_line(0);
	if (line == NULL)
		return (1); // ajouter function type clean_exit_here_doc(lim, fd)
	while (ft_strncmp(line, lim, ft_strlen(lim)) != 0)
	{
		ft_putstr_fd(line, fd);
		free(line);
		line = get_next_line(0);
		if (line == NULL)
			return (1); // ajouter function type clean_exit_here_doc(lim, fd)
	}
	return (free(line), free(lim), close(fd), 0);
}
