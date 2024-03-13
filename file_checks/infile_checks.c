/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:38:44 by ctruchot          #+#    #+#             */
/*   Updated: 2024/03/13 16:37:23 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_checks.h"
#include "minishell.h"
#include <unistd.h>

// check si des erreurs dans les fichiers,
// mais surtout si plusieurs in/outfiles, renvoie le bon (dernier)

int	error_checks(t_cmd *cmd, char **mini_env)
{
	int total_cmd;

	total_cmd = ft_cmd_lstsize(cmd);
	ft_printf("total cmd = %d\n", total_cmd);	
	check_infiles(cmd, total_cmd);
	check_outfiles(cmd, total_cmd);
	// check_options
	check_cmd(cmd, total_cmd, mini_env);

	return (0);
}

int	check_infiles(t_cmd *cmd, int total_cmd)
{
	int	cmd_nb;

	cmd_nb = 0;
	while (cmd_nb < total_cmd && cmd != NULL)
	{
		if (cmd->in)
		{
			if (check_in(cmd->in) != 0)
				kill_child(cmd);
			else
			{
				cmd->in = get_valid_in(cmd->in);
				if (cmd->in)
				{
					ft_printf("cmbnb = %d\n", cmd_nb);
					ft_printf("int = %s\n", cmd->in->path);
				}
			}
		}
		cmd_nb++;
		cmd = cmd->next;
	}
	return (0);
}

// parcourir la list d'infiles. cherche d'abord le here_doc car capte l'input
// avant d'afficher un message d'erreur, meme si l'erreur est rencontree
// avant le double chevrons

int	check_in(t_redirect *in)
{
	t_redirect	*buf;

	buf = in;
	while (in)
	{
		if (in->mode == DOUBLE)
			if (get_here_doc(in->path) != 0)
				return (1);
		in = in->next;
	}
	while (buf)
	{
		if (buf->mode == SIMPLE)
			if (check_infile_errors(buf->path) != 0)
				return (1);
		buf = buf->next;
	}
	return (0);
}

int	check_infile_errors(char *path)
{
	
	if (access(path, F_OK) != 0)
	{
		print_str_fd("no such file or directory: ", path, 2);
		return (1);
	}
	if (access(path, F_OK) == 0 && access(path, R_OK) != 0)
	{
		print_str_fd("permission denied: ", path, 2);
		return (2);
	}
	return (0);
}

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
			// si plusieurs << ds mm commande,
			// reecrivent ds mm fichier temp
			// -unlink only once,
			// pas de message d'erreur associe au unlink pour cette raison
			in = in->next;
		}
	}
	ft_in_lstclear(first_in); // verifier que tout bien clean
	return (valid_in);
}

// mm fonction mais renvoi fd
// close tous les fd sauf le dernier

// int	check_out(t_redirect *out)
// {
// 	int	fd;

// 	while (out)
// 	{
// 		if (access(out->path, F_OK) == 0 && access(out->path, W_OK) != 0)
// 		{
// 			ft_putstr_fd("permission denied: ", out->str, 2);
// 			return (0);
// 		}
// 		else if (access(out->path, F_OK) != 0)
// 		{
// 			if (out->mode == SIMPLE)
// 				if (fd = open(out->path, O_WRONLY | O_TRUNC | O_CREAT, 0644)
// 					&& fd < 0)
// 					return (0); // message d'erreur + free ?
// 			if (out->mode == DOUBLE)
// 				if (fd = open(out->path, O_WRONLY | O_APPEND | O_CREAT, 0644)
// 					&& fd < 0)
// 					return (0);
// 			if (out->next != NULL) // verifier que fonctionne
// 				close(fd);
// 		}
// 		out = out->next;
// 	}
// 	return (fd);
// }