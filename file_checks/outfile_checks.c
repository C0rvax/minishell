/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:37:33 by ctruchot          #+#    #+#             */
/*   Updated: 2024/03/13 12:41:42 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_checks.h"
#include "minishell.h"
#include <unistd.h>

// // parcourir la list d'outfiles. pour chacun, verifie les permissions ou cree
// // selon simple ou double chevrons
// // close tous les fd

int	check_outfiles(t_cmd *cmd, int total_cmd)
{
	int	cmd_nb;

	cmd_nb = 0;

	while (cmd_nb < total_cmd && cmd != NULL)
	{
		if (cmd->out)
		{
			if (check_out(cmd->out) != 0)
				kill_child(cmd);
			else
				cmd->out = get_valid_out(cmd->out);
		}
		cmd_nb++;
		cmd = cmd->next;
	}
	return (0);
}

int	check_out(t_redirect *out)
{
	while (out)
	{
		if (access(out->path, F_OK) == 0 && access(out->path, W_OK) != 0)
		{
			print_str_fd("permission denied: ", out->path, 2);
			return (3);
		}
		else if (access(out->path, F_OK) != 0)
			create_outfile(out);
		out = out->next;
	}
	return (0);
}

int	create_outfile(t_redirect *out)
{
	int	fd;

	fd = 0;
	if (out->mode == SIMPLE)
	{
		fd = open(out->path, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (fd < 0)
			return (1);
	}
	if (out->mode == DOUBLE)
	{
		fd = open(out->path, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (fd < 0)
			return (1);
	}
	close(fd);
	return (0);
}
// int	check_outfile_errors(char *path)
// {
// 	if (access(path, F_OK) == 0 && access(path, W_OK) != 0)
// 	{
// 		print_str_fd("permission denied: ", path, 2);
// 		return (3);
// 	}
// 	return (0);
// }

t_redirect	*get_valid_out(t_redirect *out)
{
	t_redirect	*valid_out;
	t_redirect	*first_out;

	first_out = out;
	valid_out = ft_in_lstlast(out);
	ft_in_lstclear(first_out);
	return (valid_out);
}
