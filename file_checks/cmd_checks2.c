/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_checks2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:32:11 by ctruchot          #+#    #+#             */
/*   Updated: 2024/03/29 16:03:34 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "file_checks.h"
#include "lexer.h"
#include "minishell.h"

// tests each paths
// returns 1 if malloc issue, with errno displayed
// returns 2 if no valid path found

int	is_valid_path(char *path, char **ptr, char *command)
{
	char	*cpypath;
	char	*cpypath2;

	cpypath = ft_strjoin(path, "/");
	if (!cpypath)
		return (ft_putstr_fd(strerror(errno), 2), 1);
	cpypath2 = ft_strjoin(cpypath, command);
	free(cpypath);
	if (!cpypath2)
		return (ft_putstr_fd(strerror(errno), 2), 1);
	if (access(cpypath2, F_OK | X_OK) == 0)
	{
		*ptr = ft_strdup(cpypath2);
		free(cpypath2);
		return (0);
	}
	else
		return (free(cpypath2), 2);
}

// checks all possible paths to keep only the valid path

char	*check_paths(char **paths, char *command, t_cmd *cmd)
{
	int		i;
	int		valid;
	char	*ptr;

	i = 0;
	valid = 1;
	ptr = NULL;
	if (!command)
		return (ft_freetab(paths), NULL);
	if (access(command, F_OK | X_OK) == 0)
	{
		ptr = ft_strdup(command);
		return (ft_freetab(paths), ptr);
	}
	while (paths[i])
	{
		valid = is_valid_path(paths[i], &ptr, command);
		if (valid == 1)
			return (ft_freetab(paths), NULL);
		else if (valid == 0)
			return (ft_freetab(paths), ptr);
		i++;
	}
	print_str_fd(command, ": command not found", "\n", 2);
	return (kill_child(cmd, 127), ft_freetab(paths), NULL);
}

// gets all the possible paths, splitting them

char	**get_all_paths(char *ptr)
{
	char	**paths;

	ptr = ft_substr(ptr, 5, ft_strlen(ptr));
	if (!ptr)
		return (ft_putstr_fd(strerror(errno), 2), NULL);
	paths = ft_split(ptr, ':');
	if (!paths)
		return (ft_putstr_fd(strerror(errno), 2), free(ptr), NULL);
	free(ptr);
	return (paths);
}
