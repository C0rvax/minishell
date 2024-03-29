/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:11:06 by ctruchot          #+#    #+#             */
/*   Updated: 2024/03/27 11:40:41 by ctruchot         ###   ########.fr       */
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
		print_str_fd("minishell: ", command, ": No such file or directory\n", 2);
		return (NULL);
	}
	return (ptr);
}

int	get_cmd_path(t_cmd *cmd, char **env, t_persistent *pers)
{
	char	*ptr;
	char	**paths;

	ptr = NULL;
	ptr = get_env(env, ptr, cmd->argv[0], cmd);
	if (ptr == NULL)
	{
		if (cmd->path_cmd == NULL)
		{
			kill_child(cmd, pers, 0);
			return (0);
		}
	}
	paths = get_all_paths(ptr);
	if (paths == NULL)
		return (1);
	cmd->path_cmd = check_paths(paths, cmd->argv[0], cmd, pers);
	if (cmd->path_cmd == NULL && cmd->type != KILLED)
		return (1);
	return (0);
}
