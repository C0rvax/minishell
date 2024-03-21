/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cd_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 19:37:13 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/21 14:07:23 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	exec_pwd_c(t_exec *exec, t_child *child)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		clear_built(exec, child, msg_built(PWD, 1));
	ft_printf("%s\n", pwd);
	clear_built(exec, child, 0);
}

void	exec_pwd(t_exec *exec)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		clean_exit_parent(exec, msg_built(PWD, 0));
	ft_printf("%s\n", pwd);
	clean_exit_parent(exec, 0);
}

// gerer les cas ou plusieurs argv (mettre un msg d'erreur)
void	exec_cd_c(t_exec *exec, t_child *child)
{
	int		fd;
	int		malloc;
	char	*built;

	malloc = 0;
	built = child->current_cmd->argv[1];
	if (!built)
	{
		built = ft_getenv(exec->mini_env, "HOME");
		malloc = 1;
	}
	if (!built)
		clear_built(exec, child, msg_built(BMALLOC, 1));
	fd = open(built, O_DIRECTORY);
	if (fd == -1)
	{
		if (malloc)
			free(built);
		clear_built(exec, child, msg_built(CD, 1));
	}
	close(fd);
	chdir(built);
	if (malloc)
		free(built);
	clear_built(exec, child, 0);
}

void	exec_cd(t_exec *exec)
{
	int		fd;
	int		malloc;
	char	*built;

	malloc = 0;
	built = exec->cmd->argv[1];
	if (!built)
	{
		built = ft_getenv(exec->mini_env, "HOME");
		malloc = 1;
	}
	if (!built)
		clean_exit_parent(exec, msg_built(BMALLOC, 0));
	fd = open(built, O_DIRECTORY);
	if (fd == -1)
	{
		if (malloc)
			free(built);
		clean_exit_parent(exec, msg_built(CD, 0));
	}
	close(fd);
	chdir(built);
	if (malloc)
		free(built);
	clean_exit_parent(exec, 0);
}
