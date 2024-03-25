/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:38:44 by ctruchot          #+#    #+#             */
/*   Updated: 2024/03/25 17:00:09 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_checks.h"
#include "minishell.h"
#include <unistd.h>

// check errors in files and cmd given
// checks all files in all cmd, then all outfiles in all cmd
// and finally all options and cmd

int	error_checks(t_cmd *cmd, char **mini_env, t_persistent	*pers)
{
	int	total_cmd;

	if (!cmd)
		return (1);
	total_cmd = ft_cmd_lstsize(cmd);
	if (total_cmd != 0)
	{
		if ((check_infiles(cmd, total_cmd, pers) != 0)
			|| (check_outfiles(cmd, total_cmd, pers) != 0)
			|| (check_cmd(cmd, total_cmd, mini_env, pers) != 0))
		{
			if (access(".tmpheredoc", F_OK) == 0)
				unlink(".tmpheredoc");
			ft_cmd_lstclear(&cmd);
			pers->status_code = 1;
			return (1);
		}	
	}
	return (0);
}

// checks through cmd list the infiles.
// in case of error in some infiles, kills the child
// if no error is encountered, only keeps the last infile for exec.
// return (1) in case of error (malloc or fd error - errno already displayed)

int	check_infiles(t_cmd *cmd, int total_cmd, t_persistent *pers)
{
	int	cmd_nb;
	int	error;

	cmd_nb = 0;
	while (cmd_nb < total_cmd && cmd != NULL)
	{
		if (cmd->in)
		{
			error = check_in(cmd->in);
			if (error == 1)
				kill_child(cmd, pers, 1);
			else if (error == 0)
			{
				cmd->in = get_valid_in(cmd->in);
				if (!cmd->in)
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

// checks through in list. first looks at the heredoc and save the input
// then prints the error message, even if the infile with error is before
// here_doc

int	check_in(t_redirect *in)
{
	t_redirect	*buf;

	buf = in;
	while (buf)
	{
		if (buf->mode == DOUBLE)
			if (get_here_doc(buf->path) != 0)
				return (2);
		buf = buf->next;
	}
	buf = in;
	while (buf)
	{
		if (buf->mode == SIMPLE)
			if (check_infile_errors(buf->path) != 0)
				return (1);
		buf = buf->next;
	}
	return (0);
}

// checks the existence and permissions in the infile if simple <

int	check_infile_errors(char *path)
{
	if (!path)
		return (3);
	if (access(path, F_OK) != 0)
	{
		print_str_fd("minishell: ", path, ": No such file or directory\n", 2);
		return (1);
	}
	if (access(path, F_OK) == 0 && access(path, R_OK) != 0)
	{
		print_str_fd("minishell: ", path, ": Permission denied\n", 2);
		return (1);
	}
	return (0);
}

// if all infiles are valid, only keeps the last one and free other infile nodes

t_redirect	*get_valid_in(t_redirect *in)
{
	t_redirect	*valid_in;
	t_redirect	*first_in;

	first_in = in;
	valid_in = ft_in_lstlast(in);
	if (valid_in->mode == DOUBLE)
		valid_in->path = ft_strdup(".tmpheredoc");
	if (valid_in->mode == SIMPLE)
	{
		while (in)
		{
			if (in->mode == DOUBLE)
				unlink(".tmpheredoc");
			in = in->next;
		}
	}
	ft_in_lstclear(first_in);
	return (valid_in);
}
