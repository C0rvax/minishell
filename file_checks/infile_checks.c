/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:38:44 by ctruchot          #+#    #+#             */
/*   Updated: 2024/04/17 14:45:25 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_checks.h"
#include "minishell.h"
#include <unistd.h>

// if all infiles are valid, only keeps the last one and free other infile nodes

t_redirect	*get_valid_in(t_redirect *in)
{
	t_redirect	*valid_in;
	t_redirect	*first_in;

	first_in = in;
	valid_in = ft_in_lstlast(in);
	if (valid_in->mode == DOUBLE)
	{
		free(valid_in->path);
		valid_in->path = ft_strdup("/tmp/.tmpheredoc");
	}
	if (valid_in->mode == SIMPLE)
	{
		while (in)
		{
			if (in->mode == DOUBLE)
				unlink("/tmp/.tmpheredoc");
			in = in->next;
		}
	}
	ft_in_lstclear(first_in);
	return (valid_in);
}

// checks the existence and permissions in the infile if simple <

static int	check_infile_errors(char *path)
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

// checks through in list. first looks at the heredoc and save the input
// then prints the error message, even if the infile with error is before
// here_doc

int	check_in(t_redirect *in, t_pers *pers)
{
	t_redirect	*buf;

	buf = in;
	while (buf)
	{
		if (buf->mode == DOUBLE)
			if (get_here_doc(buf->path, pers) != 0)
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
