/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:38:44 by ctruchot          #+#    #+#             */
/*   Updated: 2024/03/19 15:56:10 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_checks.h" 
#include "minishell.h"
#include <unistd.h>

// check errors in files and cmd given
// checks all files in all cmd, then all outfiles in all cmd
// and finally all options and cmd

// Cam c'est normale que la fonction renvoie tjrs 0 ??
int	error_checks(t_cmd *cmd, char **mini_env)
{
	int	total_cmd;

	if (!cmd)
		return (1);
	total_cmd = ft_cmd_lstsize(cmd);
	// si total_cmd = 0, quid sur exec ?
	ft_printf("total cmd = %d\n", total_cmd);
	if (total_cmd != 0)
	{
		if (check_infiles(cmd, total_cmd) != 0)
			return (1); //slmt si malloc pete mettre fin au prog
		if (check_outfiles(cmd, total_cmd) != 0)
			return (1); // seulement si pb de fd
		// check_options
		if (check_cmd(cmd, total_cmd, mini_env) != 0)
			return (1); // slmt pb de malloc aussi
	}
	return (0);
}

// checks through cmd list the infiles.
// in case of error in some infiles, kills the child but continues through cmd

int	check_infiles(t_cmd *cmd, int total_cmd)
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
				kill_child(cmd);
			else if (error == 0)
			{
				cmd->in = get_valid_in(cmd->in);
				if (!cmd->in)
					return (1); // relevant de sortir de la fonction?
				ft_printf("cmbnb = %d\n", cmd_nb);
				ft_printf("int = %s\n", cmd->in->path);
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
// then prints the error message, even if the infile with error 
// is before here_doc

int	check_in(t_redirect *in)
{
	t_redirect	*buf;

	buf = in;
	while (in)
	{
		if (in->mode == DOUBLE)
			if (get_here_doc(in->path) != 0)
				return (2); // 2 si malloc ou fd pete -> strerror
		in = in->next;
	}
	while (buf)
	{
		if (buf->mode == SIMPLE)
			if (check_infile_errors(buf->path) != 0)
				return (1); // 1 si erreur de fichier
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
		print_str_fd("no such file or directory: ", path, "\n", 2);
		return (1);
	}
	if (access(path, F_OK) == 0 && access(path, R_OK) != 0)
	{
		print_str_fd("permission denied: ", path, "\n", 2);
		return (2);
	}
	return (0);
}

// if all infiles are valid, only keeps the last one and free other in nodes

t_redirect	*get_valid_in(t_redirect *in)
{
	t_redirect	*valid_in;
	t_redirect	*first_in;

	first_in = in;
	valid_in = ft_in_lstlast(in);
	if (valid_in->mode == DOUBLE)
		valid_in->path = ".tmpheredoc";
	if (valid_in->mode == SIMPLE)
	{
		while (in)
		{
			if (in->mode == DOUBLE)
				unlink(".tmpheredoc");
			// @Corvax : si plusieurs << ds mm commande,
			// reecrivent ds mm fichier temp
			// -unlink only once,
			// pas de message d'erreur associe au unlink pour cette raison
			in = in->next;
		}
	}
	ft_in_lstclear(first_in); // verifier que tout bien clean
	return (valid_in);
}
