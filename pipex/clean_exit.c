/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 22:53:39 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/05 18:36:17 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_struct(t_data *data)
{
	int	i;

	i = 0;
	if (data->paths)
		ft_freetab(data->paths);
	if (data->fd)
		free(data->fd);
	if (data->pipefd)
	{
		while (i < data->cmd_max - 1)
		{
			free(data->pipefd[i]);
			i++;
		}
		free(data->pipefd);
	}
	if (data->pid)
		free(data->pid);
}

void	print_error(char *s1, char *s2)
{
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(s2, 2);
	ft_putstr_fd("\n", 2);
}

void	clean_exit(t_data *data, t_err error, int status_code)
{
	if (error == MALLOC)
		print_error("pipex", strerror(errno));
	if (error == PIPE)
		print_error("pipe", "Failure");
	if (error == CMD)
		print_error("command not found", data->argv[0]);
	if (error == DUP)
		print_error("dup2", "Failure");
	if (error == EXEC)
		print_error(data->argv[0], strerror(errno));
	if (error == FORK)
		print_error("fork", strerror(errno));
	if (error == OUTFILE)
		print_error(strerror(errno), data->av[4 + data->hd]);
	if (data->argv)
		ft_freetab(data->argv);
	close_file(data);
	free_struct(data);
	exit(status_code);
}
/*
*/
