/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:11:06 by ctruchot          #+#    #+#             */
/*   Updated: 2024/03/25 18:55:31 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "file_checks.h"
#include "lexer.h"
#include "minishell.h"

// possible plusieurs cmd ???

// checks through cmd list the cmd path.
// if no argv[0], kills the child.
// checks if is a builtin and mark them as such
// returns 1 in case of malloc issue

int check_builtins(t_cmd *cmd, int total_cmd)
{
	int		i;

	i = -1;
	i = is_a_builtin(cmd);
	if (i != -1)
	{
		if (total_cmd == 1)
		{
			cmd->type = BUILTPAR;
			return (1);
		}
		else if (total_cmd > 1)
		{
			cmd->type = BUILTCHILD;
			return (1);
		}
	}
	return (0);
}

void kill_child(t_cmd *cmd, t_persistent *pers, int code)
{
	cmd->type = KILLED;
	cmd->code_err = code;
	pers->status_code = code;
}

int	check_cmd(t_cmd *cmd, int total_cmd, char **env, t_persistent *pers)
{
	char	*ptr;
	char	**paths;
	int		cmd_nb;
	
	cmd_nb = 0;
	ptr = NULL;
	while (cmd_nb < total_cmd && cmd != NULL)
	{
		if (!cmd->argv || cmd->argv[0] == NULL)
			kill_child(cmd, pers, 1); // 127 ??
		if (cmd->type != KILLED)
		{
			if (check_builtins(cmd, total_cmd) != 0)
				return (0);
			ptr = get_env(env, ptr, cmd->argv[0], cmd);
			if (ptr == NULL)
				if (cmd->path_cmd == NULL)
					kill_child(cmd, pers, 127);
			paths = get_all_paths(ptr);
			if (paths == NULL)
				return (1);
			cmd->path_cmd = check_paths(paths, cmd->argv[0], cmd, pers);
			if (cmd->path_cmd == NULL && cmd->type != KILLED)
				return (1);
		}
		cmd_nb++;
		cmd = cmd->next;
	}
	return (0);
}

// gets the env PATH variable

char	*get_env(char **env, char *ptr, char *command, t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!command)
		return (NULL);
	while (ptr == NULL && env[i])
	{
		ptr = ft_strnstr(env[i], "PATH=", 5);
		i++;
	}
	if (!ptr)
	{
		if (access(command, F_OK | X_OK) == 0)
		{
			cmd->path_cmd = ft_strdup(command);
			return (NULL);
		}
		print_str_fd(command, "No such file or directory", "\n", 2);
		// ok avec ce message? comme ds bash si PATH supprime
		return (NULL);
	}
	return (ptr);
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

// checks all possible paths to keep only the valid path

char	*check_paths(char **paths, char *command, t_cmd *cmd, t_persistent *pers)
{
	int		i;
	int		valid;
	char	*ptr;

	i = 0;
	valid = 1;
	ptr = NULL;
	if (!command)
		return (free_tab(paths), NULL);
	if (access(command, F_OK | X_OK) == 0)
	{
		ptr = ft_strdup(command);
		return (free_tab(paths), ptr);
	}
	while (paths[i])
	{
		valid = is_valid_path(paths[i], &ptr, command);
		if (valid == 1)
			return (free_tab(paths), NULL);
		else if (valid == 0)
			return (free_tab(paths), ptr);
		i++;
	}
	print_str_fd("command not found: ", command, "\n", 2);
	kill_child(cmd, pers, 127);
	return (free_tab(paths), NULL);
}

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
