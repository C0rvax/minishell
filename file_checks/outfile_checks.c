/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:37:33 by ctruchot          #+#    #+#             */
/*   Updated: 2024/03/22 16:04:21 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_checks.h"
#include "minishell.h"
#include <unistd.h>

// checks through cmd list the outfiles.
// in case of error in some outfiles, kills the child.
// if all outfiles are OK, it only keeps the last one.
// return 1 in case of mistake in fd opening (strerror already displayed)

int	check_outfiles(t_cmd *cmd, int total_cmd)
{
	int	cmd_nb;
	int	error;

	cmd_nb = 0;
	error = 0;
	while (cmd_nb < total_cmd && cmd != NULL)
	{
		if (cmd->out && cmd->type != KILLED)
		{
			error = check_out(cmd->out);
			if (error == 1)
				cmd->type = KILLED;
			else if (error == 0)
			{
				cmd->out = get_valid_out(cmd->out);
				if (!cmd->out)
					return (1);
			}
			else
				return (1);
		}
		cmd_nb++;
		cmd = cmd->next;
	}
	return (0);
}

//checks if outfile exists and the relevant permissions
// if outfile does not exist, creates it

int	check_out(t_redirect *out)
{
	while (out)
	{
		if (!out->path)
			return (1); // @Corvax: verifier que message dérreur prevu au parsing
		if (access(out->path, F_OK) == 0 && access(out->path, W_OK) != 0)
		{
			print_str_fd("permission denied: ", out->path, "\n", 2);
			return (1);
		}
		else if (access(out->path, F_OK) != 0)
			if (create_outfile(out) != 0)
				return (3);
		out = out->next;
	}
	return (0);
}

// creates the outfile depending on the simple < or double <<

int	create_outfile(t_redirect *out)
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
