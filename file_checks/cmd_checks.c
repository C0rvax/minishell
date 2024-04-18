/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:11:06 by ctruchot          #+#    #+#             */
/*   Updated: 2024/04/18 17:51:09 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "file_checks.h"
#include "lexer.h"
#include "minishell.h"

int	check_builtins(t_cmd *cmd, int total_cmd)
{
	int	i;

	i = -1;
	i = is_a_builtin(cmd);
	if (i != -1 && i != 7)
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

int	is_directory(t_cmd *cmd, t_pers *pers, int total_cmd)
{
	int	fd;

	fd = 0;
	fd = open(cmd->argv[0], O_DIRECTORY);
	if (fd > 0)
	{
		close(fd);
		if (ft_strcmp(cmd->argv[0], ".") == 0)
		{
			print_str_fd("minishell: .: filename argument required\n",
				NULL, NULL, 2);
			print_str_fd(".: usage: . filename [arguments]\n", NULL, NULL, 2);
			if (kill_child(cmd, 2, pers, total_cmd) != 0)
				return (1);
			return (2);
		}
		print_str_fd("minishell: ", cmd->argv[0], ": Is a directory\n", 2);
		if (kill_child(cmd, 126, pers, total_cmd) != 0)
			return (1);
		return (2);
	}
	return (0);
}

// gets the env PATH variable

static char	*get_env(char **env, char *ptr, char *command, t_cmd *cmd)
{
	int	i;

	i = 0;
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
		print_str_fd("minishell: ", command, ": No such file or directory\n",
			2);
		return (NULL);
	}
	return (ptr);
}
// first get the env variable PATH. 
// If it is not found, it tests whether the command is executable by itself
// (either because absolute path, or because is executable).
// if not, kill the child - either it was the only child and therefore returns
// 1, or it is not the only one and return 0, so that the program continues
// to check whether other commands may be executed

// update status_code ????

// creates an array from the paths - in case of malloc issue, returns 2
// then, if path_cmd was not found as an executable in the absence of PATH,
// send to check_paths
// if path_cmd still null while the child is not killed - this is an issue

int	get_cmd_path(t_cmd *cmd, char **env, t_pers *pers, int total_cmd)
{
	char	*ptr;
	char	**paths;

	ptr = NULL;
	ptr = get_env(env, ptr, cmd->argv[0], cmd);
	if (ptr == NULL)
	{
		if (cmd->path_cmd == NULL)
		{
			if (kill_child(cmd, 127, pers, total_cmd) != 0)
				return (1);
			return (0);
		}
	}
	paths = get_all_paths(ptr);
	if (cmd->path_cmd == NULL)
	{
		cmd->path_cmd = check_paths(paths, cmd->argv[0], cmd, pers);
		if (cmd->path_cmd == NULL)
			if (cmd->type != KILLED || total_cmd == 1)
				return (2);
	}
	return (0);
}
