/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 12:33:23 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/05 17:03:18 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	set_first(t_data *data)
{
	int	error;

	close(data->pipefd[data->cmd_n][0]);
	error = dup2(data->fd[0], 0);
	if (error == -1)
		clean_exit(data, DUP, 1);
	error = dup2(data->pipefd[data->cmd_n][1], 1);
	if (error == -1)
		clean_exit(data, DUP, 1);
}

static void	set_last(t_data *data)
{
	int	error;

	close(data->pipefd[data->cmd_n - 1][1]);
	error = dup2(data->pipefd[data->cmd_n - 1][0], 0);
	if (error == -1)
		clean_exit(data, DUP, 1);
	error = dup2(data->fd[1], 1);
	if (error == -1)
		clean_exit(data, DUP, 1);
}

static void	set_middle(t_data *data)
{
	int	error;

	close(data->pipefd[data->cmd_n - 1][1]);
	close(data->pipefd[data->cmd_n][0]);
	error = dup2(data->pipefd[data->cmd_n - 1][0], 0);
	if (error == -1)
		clean_exit(data, DUP, 1);
	error = dup2(data->pipefd[data->cmd_n][1], 1);
	if (error == -1)
		clean_exit(data, DUP, 1);
}

void	exec_cmd(t_data *data)
{
	int	error;

	if (data->cmd_n == 0)
		set_first(data);
	else if (data->cmd_n == data->cmd_max - 1)
		set_last(data);
	else
		set_middle(data);
	init_argv(data);
	close_file(data);
	free_struct(data);
	error = execve(data->cmd, data->argv, data->env);
	if (error == -1)
		clean_exit(data, EXEC, 1);
}
