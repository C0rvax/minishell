/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_checks2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:32:11 by ctruchot          #+#    #+#             */
/*   Updated: 2024/04/15 14:23:13 by ctruchot         ###   ########.fr       */
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

static void	not_found(char **paths, char *comnd, t_cmd *cmd)
{
	print_str_fd(comnd, " : command not found", "\n", 2);
	kill_child(cmd, 127);
	ft_freetab(paths);
}

static char	*check_executables(char **paths, char *comnd, char *ptr)
{
	if (access(comnd, F_OK | X_OK) == 0)
	{
		ptr = ft_strdup(comnd);
		return (ft_freetab(paths), ptr);
	}
	return (NULL);
}

// checks all possible paths to keep only the valid path

char	*check_paths(char **paths, char *comnd, t_cmd *cmd)
{
	int		i;
	int		valid;
	char	*ptr;

	i = -1;
	valid = 1;
	ptr = NULL;
	if (!comnd)
		return (ft_freetab(paths), NULL);
	if (comnd[0] == '\0')
		return (not_found(paths, comnd, cmd), NULL);
	while (paths && paths[++i])
	{
		valid = is_valid_path(paths[i], &ptr, comnd);
		if (valid == 1)
			return (ft_freetab(paths), NULL);
		else if (valid == 0)
			return (ft_freetab(paths), ptr);
	}
	if (ft_strcmp(comnd, "a.out") == 0 || ft_strcmp(comnd, "minishell") == 0)
		return (not_found(paths, comnd, cmd), NULL);
	ptr = check_executables(paths, comnd, ptr);
	if (ptr != NULL)
			return (ptr);
	return (not_found(paths, comnd, cmd), NULL);
}

// gets all the possible paths, splitting them

char	**get_all_paths(char *ptr)
{
	char	**paths;

	if (!ptr)
		return (NULL);
	ptr = ft_substr(ptr, 5, ft_strlen(ptr));
	if (!ptr)
		return (ft_putstr_fd(strerror(errno), 2), NULL);
	paths = ft_split(ptr, ':');
	if (!paths)
		return (ft_putstr_fd(strerror(errno), 2), free(ptr), NULL);
	free(ptr);
	return (paths);
}
