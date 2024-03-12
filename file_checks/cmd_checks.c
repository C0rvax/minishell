/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:11:06 by ctruchot          #+#    #+#             */
/*   Updated: 2024/03/12 22:48:01 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_checks.h"
#include "minishell.h"

int	check_cmd(t_cmd *cmd, int total_cmd, char **env)
{
	char	*ptr;
	char	**paths;
	int		cmd_nb;

	cmd_nb = 0;
	while (cmd_nb < total_cmd && cmd != NULL)
	{
		if (cmd->argv)
		{
			ptr = NULL;
			ptr = get_env(env, ptr, cmd->argv[0], cmd);
			if (ptr == NULL)
			{
				if (cmd->path_cmd == NULL)
					kill_child(cmd);
				return (0);
			}
			paths = get_all_paths(ptr);
			if (paths == NULL)
				return (1); 
			cmd->path_cmd = check_paths(paths, cmd->argv[0]);
			if (cmd->path_cmd == NULL)
				return (1);
		}
		cmd_nb++;
		cmd = cmd->next;
	}
	return (0);
}

char	*get_env(char **env, char *ptr, char *command, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (ptr == NULL && env[i])
	{
		ptr = ft_strnstr(env[i], "PATH=", 5);
		i++;
	}
	if (ptr == NULL)
	{
		if (access(command, F_OK | X_OK) == 0)
		{
			cmd->path_cmd = command;
			return (NULL);
		}
		ft_putstr_fd(command, 2);
		ft_putstr_fd("No such file or directory\n", 2); // ok avec ce message? comme ds bash si PATH supprime
		return (NULL);
	}
	return (ptr);
}

// gets all the possible paths, splitting them

char	**get_all_paths(char *ptr)
{
	char	**paths;

	ptr = ft_substr(ptr, 5, ft_strlen(ptr));
	paths = ft_split(ptr, ':');
	if (paths == NULL)
	{
		if (ptr != NULL)
			free(ptr);
		ft_putstr_fd(strerror(errno), 2);
		return (NULL);
	}
	free(ptr);
	return (paths);
}

// checks all possible paths to keep only the valid path

char	*check_paths(char **paths, char *command)
{
	int		i;
	char	*cpypath;
	char	*cpypath2;

	cpypath2 = NULL;
	i = 0;
	if (access(command, F_OK | X_OK) == 0)
		return (free_tab(paths), command);
	while (paths[i])
	{
		if (cpypath2 != NULL)
			free(cpypath2);
		cpypath = ft_strjoin(paths[i], "/");
		cpypath2 = ft_strjoin(cpypath, command);
		free(cpypath);
		if (access(cpypath2, F_OK | X_OK) == 0)
			return (free_tab(paths), cpypath2);
		i++;
	}
	ft_putstr_fd("command not found: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd("\n", 2);
	return (free_tab(paths), free(cpypath2), NULL);
}
