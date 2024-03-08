/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 23:19:50 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/05 16:32:24 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	print_hd(int cmd)
{
	while (cmd > 1)
	{
		ft_printf("pipe ");
		cmd--;
	}
	ft_printf("heredoc> ");
}

static void	init_hd(t_data *data)
{
	int		fd;
	char	*line;

	fd = open(".hd", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	print_hd(data->cmd_max);
	line = get_next_line(0);
	while (line)
	{
		if (!ft_strncmp(line, data->av[2], ft_strlen(line) - 1)
			&& ft_strlen(data->av[2]) == ft_strlen(line) - 1)
		{
			free(line);
			close (fd);
			return ;
		}
		else
			ft_putstr_fd(line, fd);
		free(line);
		print_hd(data->cmd_max);
		line = get_next_line(0);
	}
	close(fd);
}

void	open_file(t_data *data)
{
	char	*outfile;

	outfile = data->av[data->cmd_max + 2 + data->hd];
	if (data->hd)
	{
		init_hd(data);
		data->fd[0] = open(".hd", O_RDONLY);
		if (data->fd[0] == -1)
			print_error(strerror(errno), data->av[1 + data->hd]);
		data->fd[1] = open(outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
	}
	else
	{
		data->fd[0] = open(data->av[1], O_RDONLY);
		if (data->fd[0] == -1)
			print_error(strerror(errno), data->av[1 + data->hd]);
		data->fd[1] = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	if (data->fd[1] == -1)
		clean_exit(data, OUTFILE, 1);
	if (data->fd[0] == -1)
		clean_exit(data, INFILE, 0);
}

void	close_file(t_data *data)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		if (data->fd[i] >= 0)
			close(data->fd[i]);
		i++;
	}
	i = 0;
	while (i < data->cmd_max - 1)
	{
		if (data->pipefd[i][0] >= 0)
			close(data->pipefd[i][0]);
		if (data->pipefd[i][1] >= 0)
			close(data->pipefd[i][1]);
		i++;
	}
	if (data->hd)
		unlink(".hd");
}
