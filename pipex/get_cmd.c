/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 14:59:45 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/05 18:01:42 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_cmd(char *cmd, t_data *data)
{
	int		i;
	int		a;
	char	*path;

	i = 0;
	if (data->paths)
	{
		while (data->paths[i])
		{
			path = ft_strjoin(data->paths[i], cmd);
			if (!path)
				return (NULL);
			a = access(path, F_OK | X_OK);
			if (a == 0)
				return (path);
			free(path);
			path = NULL;
			i++;
		}
	}
	a = access(cmd, F_OK | X_OK);
	if (a == 0)
		return (cmd);
	return (NULL);
}

void	init_argv(t_data *data)
{
	data->argv = ft_split(data->av[data->cmd_n + 2 + data->hd], ' ');
	if (!data->argv)
		clean_exit(data, MALLOC, 1);
	data->cmd = get_cmd(data->argv[0], data);
	if (!data->cmd)
		clean_exit(data, CMD, 127);
}
