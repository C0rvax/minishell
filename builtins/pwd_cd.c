/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 19:37:13 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/25 17:09:46 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

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

void	exec_pwd_c(t_exec *exec, t_child *child)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		clear_built(exec, child, msg_built(PWD, strerror(errno), 1));
	ft_printf("%s\n", pwd);
	free(pwd);
	clear_built(exec, child, 0);
}

int	exec_pwd(t_exec *exec)
{
	char	*pwd;
	int		fd;

	fd = redirect_out(exec);
	if (fd < 0)
		return (clear_one(exec, msg_built(FD, exec->cmd->argv[1], 1)));
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (clear_one(exec, msg_built(PWD, strerror(errno), 1)));
	ft_putstr_fd(pwd, fd);
	ft_putstr_fd("\n", fd);
	free(pwd);
	if (fd != 1)
		close(fd);
	return (clear_one(exec, 0));
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
		return (clear_one(exec, msg_built(ARGS, "cd", 2)));
	built = exec->cmd->argv[1];
	if (!built)
	{
		built = ft_getenv(exec->mini_env, "HOME");
		malloc = 1;
	}
	if (!built)
		return (clear_one(exec, msg_built(BMALLOC, strerror(errno), 1)));
	if (!built[0])
		return (clear_one(exec, msg_built(CD, strerror(errno), 1)));
	if (test_path(built, malloc))
		return (clear_one(exec, msg_built(CD, strerror(errno), 1)));
	chdir(built);
	if (malloc)
		free(built);
	return (clear_one(exec, 0));
}
