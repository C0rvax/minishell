/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_checks2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:32:11 by ctruchot          #+#    #+#             */
/*   Updated: 2024/04/17 17:38:44 by ctruchot         ###   ########.fr       */
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

static void	not_found(char **paths, char *comnd, t_cmd *cmd, t_pers *pers)
{
	print_str_fd(comnd, " : command not found", "\n", 2);
	kill_child(cmd, 127, pers, 0);
	if (paths)
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
// if comnd[0] is \0 (if "" for instance) - returns NULL after
// printing a not found message and killing the child
// them for each path, it tests its validity
// 1 is for an issue, 0 if path is valid or 2 if not valid
// returns NULL in case of issue and ptr if path is found
// continunes only if path not found yes - checks whether the command
// is a.out or minishell - they should not execute as is but with ./ before
// then it checks whether the command is executable per itself
// returns NULL if not after killing the child.

char	*check_paths(char **paths, char *comnd, t_cmd *cmd, t_pers *pers)
{
	int		i;
	int		valid;
	char	*ptr;

	i = -1;
	valid = 1;
	ptr = NULL;
	if (paths == NULL)
		return (not_found(paths, comnd, cmd, pers), NULL);
	if (comnd[0] == '\0')
		return (not_found(paths, comnd, cmd, pers), NULL);
	while (paths && paths[++i])
	{
		valid = is_valid_path(paths[i], &ptr, comnd);
		if (valid == 1)
			return (ft_freetab(paths), NULL);
		else if (valid == 0)
			return (ft_freetab(paths), ptr);
	}
	if (ft_strcmp(comnd, "a.out") == 0 || ft_strcmp(comnd, "minishell") == 0)
		return (not_found(paths, comnd, cmd, pers), NULL);
	ptr = check_executables(paths, comnd, ptr);
	if (ptr)
		return (ptr);
	return (not_found(paths, comnd, cmd, pers), NULL);
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
