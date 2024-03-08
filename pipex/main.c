/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:42:31 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/08 12:35:13 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	wait_and_clean(t_data *data)
{
	int	status;
	int	status_code;
	int	i;

	i = 0;
	status_code = 0;
	close_file(data);
	while (i < data->cmd_max)
	{
		waitpid(data->pid[i], &status, 0);
		if (i == data->cmd_max - 1 && WIFEXITED(status))
		{
			status_code = WEXITSTATUS(status);
		}
		i++;
	}
	free_struct(data);
	return (status_code);
}

int	pipex(int ac, char **av, char **env)
{
	t_data	data;
	int		status_code;

	data.cmd_n = 0;
	while (data.cmd_n < data.cmd_max)
	{
		data.pid[data.cmd_n] = fork();
		if (data.pid[data.cmd_n] == -1)
			clean_exit(&data, FORK, 1);
		if (data.pid[data.cmd_n] == 0)
			exec_cmd(&data);
		data.cmd_n++;
	}
	status_code = wait_and_clean(&data);
	return (status_code);
}
