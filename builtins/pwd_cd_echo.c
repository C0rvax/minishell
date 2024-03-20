/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cd_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 19:37:13 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/20 19:59:05 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	exec_pwd(t_exec *exec, t_child *child)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		clear_built(exec, child, msg_built(PWD, 1));
	ft_printf("%s\n", pwd);
	clear_built(exec, child, 0);
}

// gerer les cas ou plusieurs argv (mettre un msg d'erreur)
void	exec_cd(t_exec *exec, t_child *child)
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

int	check_flag_echo(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (1);
	while (str[++i])
	{
		if (str[i] != 'n')
			return (1);
	}
	return (0);
}

void	exec_echo(t_exec *exec, t_child *child)
{
	int		i;
	char	**buf;

	buf = child->current_cmd->argv;
	i = 1;
	if (!buf[1])
		ft_printf("\n");
	else if (buf[1] && !check_flag_echo(buf[1]))
	{
		i = 0;
		while (buf[++i])
			ft_printf("%s", buf[i]);
	}
	else if (buf[1] && check_flag_echo(buf[1]))
	{
		i = 0;
		while (buf[++i])
			ft_printf("%s", buf[i]);
		ft_printf("\n");
	}
	clear_built(exec, child, 0);
}
