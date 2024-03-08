/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 01:31:54 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/06 14:36:23 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	init_malloc(t_data *data)
{
	int	i;

	i = 0;
	data->fd = malloc(sizeof(int) * 2);
	if (!data->fd)
		clean_exit(data, MALLOC, 1);
	data->fd[0] = -2;
	data->fd[1] = -2;
	data->pipefd = malloc(sizeof(int *) * (data->cmd_max - 1));
	if (!data->pipefd)
		clean_exit(data, MALLOC, 1);
	while (i < data->cmd_max - 1)
	{
		data->pipefd[i] = malloc(sizeof(int) * 2);
		if (!data->pipefd[i])
			clean_exit(data, MALLOC, 1);
		data->pipefd[i][0] = -2;
		data->pipefd[i][1] = -2;
		i++;
	}
	data->pid = malloc(sizeof(int) * data->cmd_max);
	if (!data->pid)
		clean_exit(data, MALLOC, 1);
	data->pid[0] = -2;
	data->pid[1] = -2;
}

static void	init_pipe(t_data *data)
{
	int	p;
	int	i;

	i = 0;
	while (i < data->cmd_max - 1)
	{
		p = pipe(data->pipefd[i]);
		if (p == -1)
			clean_exit(data, PIPE, 1);
		i++;
	}
}

static char	**add_slash(char **path)
{
	int		i;
	char	*copy;

	i = 0;
	while (path[i])
	{
		copy = path[i];
		path[i] = ft_strjoin(path[i], "/");
		free(copy);
		if (!path[i])
			return (ft_freetab(path), NULL);
		i++;
	}
	return (path);
}

static void	get_paths(t_data *data)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	while (data->env[i])
	{
		if (ft_strnstr(data->env[i], "PATH=", 5))
		{
			path = ft_substr(data->env[i], 5, ft_strlen(data->env[i]));
			if (!path)
				clean_exit(data, MALLOC, 1);
			data->paths = ft_split(path, ':');
			free(path);
			if (!data->paths)
				clean_exit(data, MALLOC, 1);
			data->paths = add_slash(data->paths);
			return ;
		}
		i++;
	}
}

t_data	init_struct(int ac, char **av, char **env)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	data.av = av;
	data.env = env;
	if (!ft_strncmp(av[1], "here_doc", ft_strlen(av[1])))
		data.hd = 1;
	data.cmd_max = ac - 3 - data.hd;
	get_paths(&data);
	init_malloc(&data);
	open_file(&data);
	init_pipe(&data);
	return (data);
}
