/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:37:33 by ctruchot          #+#    #+#             */
/*   Updated: 2024/04/18 16:47:16 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_checks.h"
#include "minishell.h"

// if no error is encountered, keeps only the last outfile for exec

t_redirect	*get_valid_out(t_redirect *out)
{
	t_redirect	*valid_out;
	t_redirect	*first_out;

	first_out = out;
	valid_out = ft_in_lstlast(out);
	ft_in_lstclear(first_out);
	return (valid_out);
}

// creates the outfile depending on the simple < or double <<

static int	create_outfile(t_redirect *out)
{
	int	fd;

	fd = 0;
	if (out->mode == SIMPLE)
	{
		fd = open(out->path, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (fd < 0)
			return (ft_putstr_fd(strerror(errno), 2), 1);
	}
	if (out->mode == DOUBLE)
	{
		fd = open(out->path, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (fd < 0)
			return (ft_putstr_fd(strerror(errno), 2), 1);
	}
	close(fd);
	return (0);
}

//checks if outfile exists and the relevant permissions
// if outfile does not exist, creates it

int	check_out(t_redirect *out)
{
	while (out)
	{
		if (!out->path)
			return (1);
		if (access(out->path, F_OK) == 0 && access(out->path, W_OK) != 0)
		{
			print_str_fd("minishell: ", out->path, ": Permission denied\n", 2);
			return (1);
		}
		if (create_outfile(out) != 0)
			return (2);
		out = out->next;
	}
	return (0);
}
