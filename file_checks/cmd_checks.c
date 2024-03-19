/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:11:06 by ctruchot          #+#    #+#             */
/*   Updated: 2024/03/19 12:39:32 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_checks.h"
#include "minishell.h"
// si malloc pete -> on free la commande et 
// on renvoie le prompt / distinguer de cas ou pas de commande 

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
				if (cmd->path_cmd == NULL)
					kill_child(cmd);
			paths = get_all_paths(ptr);
			if (paths == NULL)
				return (1);
			cmd->path_cmd = check_paths(paths, cmd->argv[0], cmd);
			if (cmd->path_cmd == NULL && cmd->type != KILLED)
				return (1); // enfant pas tue donc si pb malloc
			ft_printf("cmbnb = %d\n", cmd_nb);
			ft_printf("cmd = %s\n", cmd->path_cmd);
			if (cmd->type == KILLED)
				ft_printf("KILLED");
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
			cmd->path_cmd = command;
			return (NULL);
		}
		print_str_fd(command, "No such file or directory", "\n", 2); // ok avec ce message? comme ds bash si PATH supprime
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

char	*check_paths(char **paths, char *command, t_cmd *cmd)
{
	int		i;
	int		valid;
	char	*ptr;

	i = 0;
	valid = 1;
	ptr = malloc(sizeof(char));
	ptr[0] = '\0';
	if (!command)
		return (free_tab(paths), NULL);
	if (access(command, F_OK | X_OK) == 0)
		return (free_tab(paths), command);
	while (paths[i])
	{
		valid = is_valid_path(paths[i], &ptr, command);
		if (valid == 1) // = malloc
			return (free_tab(paths), NULL);
		else if (valid == 0) // = valid path
			return (free_tab(paths), ptr);
		i++;
	}
	print_str_fd("command not found: ", command, "\n", 2);
	kill_child(cmd); //meme retour si pb ou si command not found
	return (free_tab(paths), NULL);
}

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
		free(*ptr);
		*ptr = NULL;
		*ptr = cpypath2;
		return (0);
	}
	else
		return (2);
}
