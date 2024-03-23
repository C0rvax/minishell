/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 19:37:13 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/23 18:30:20 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	exec_pwd_c(t_exec *exec, t_child *child)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		clear_built(exec, child, msg_built(PWD, strerror(errno), 1));
	ft_printf("%s\n", pwd);
	clear_built(exec, child, 0);
}

int	exec_pwd(t_exec *exec)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (clean_exit_parent(exec, msg_built(PWD, strerror(errno), 1)));
	ft_printf("%s\n", pwd);
	return (clean_exit_parent(exec, 0));
}

// gerer les cas ou plusieurs argv (mettre un msg d'erreur)
static int	test_path(char *path, int malloc)
{
	int	fd;

	fd = open(path, O_DIRECTORY);
	if (fd == -1)
	{
		if (malloc)
			free(path);
		return (1);
	}
	close(fd);
	return (0);
}

void	exec_cd_c(t_exec *exec, t_child *child)
{
	int		malloc;
	char	*built;

	malloc = 0;
	if (child->current_cmd->argv[1] && child->current_cmd->argv[2])
		clear_built(exec, child, msg_built(ARGS, "cd", 2));
	built = child->current_cmd->argv[1];
	if (!built)
	{
		built = ft_getenv(exec->mini_env, "HOME");
		malloc = 1;
	}
	if (!built)
		clear_built(exec, child, msg_built(BMALLOC, strerror(errno), 1));
	if (!built[0])
		clear_built(exec, child, msg_built(CD, strerror(errno), 1));
	if (test_path(built, malloc))
		clear_built(exec, child, msg_built(CD, strerror(errno), 1));
	chdir(built);
	if (malloc)
		free(built);
	clear_built(exec, child, 0);
}

int	exec_cd(t_exec *exec)
{
	int		malloc;
	char	*built;

	malloc = 0;
	if (exec->cmd->argv[1] && exec->cmd->argv[2])
		return (clean_exit_parent(exec, msg_built(ARGS, "cd", 2)));
	built = exec->cmd->argv[1];
	if (!built)
	{
		built = ft_getenv(exec->mini_env, "HOME");
		malloc = 1;
	}
	if (!built)
		return (clean_exit_parent(exec, msg_built(BMALLOC, strerror(errno), 1)));
	if (!built[0])
		return (clean_exit_parent(exec, msg_built(CD, strerror(errno), 1)));
	if (test_path(built, malloc))
		return (clean_exit_parent(exec, msg_built(CD, strerror(errno), 1)));
	chdir(built);
	if (malloc)
		free(built);
	return (clean_exit_parent(exec, 0));
}
