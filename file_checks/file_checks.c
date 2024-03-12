/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:38:44 by ctruchot          #+#    #+#             */
/*   Updated: 2024/03/12 16:50:20 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "file_checks.h"
#include <unistd.h>

// check si des erreurs dans les fichiers, 
// mais surtout si plusieurs in/outfiles, renvoie le bon (dernier)

int	error_checks(t_cmd *cmd)
{
	int	total_cmd; // externaliser ca
	int	cmd_nb;

	cmd_nb = 0;
	total_cmd = ft_cmd_lstsize(cmd);
	
	check_infiles
	check_outfiles
	check_options
	check_cmd
	
	while (cmd_nb < total_cmd && cmd != NULL) // parcourir les enfants // necessaire d'avoir les 2 conditions?
	{
		if (cmd->in)
		{
			if (check_in(cmd->in) != 0)
				return (1);
			cmd->in = get_valid_in(cmd->in); // verifier que els precedents sont bien free
		}
		if (cmd->in)
			ft_printf("cmd-in=%s\n", cmd->in->path);
		if (cmd->out)
		{
			if (check_out(cmd->out) != 0)
				return (1);
			cmd->out = get_valid_out(cmd->out); // on perd les in precedents, il faut les free
			// fdout = check_out(cmd->out) // j'en fais quoi de mon fd ?? sinon je close tout et je rouvre ailleur
			// if (fdout = 0)
			// 	return (1);
		}
		if (cmd->out)
			ft_printf("cmd-out=%s\n", cmd->out->path);
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
			if (check_infile(buf->path) != 0)
				return (1);
		buf = buf->next;
	}
	return (0);
}

int	check_infile(char *path)
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

t_redirect *get_valid_in(t_redirect *in)
{
	t_redirect *valid_in;
	t_redirect *first_in;

	first_in = in;
	valid_in = ft_in_lstlast(in);
	if (valid_in->mode == DOUBLE)
		valid_in->path = ".tmpheredoc";
	if (valid_in->mode == SIMPLE)
	{
		while (in)
		{
			if (in->mode == DOUBLE) // si plusieurs << ds mm commande, 
			// reecrivent ds mm fichier temp - unlink only once, 
			// pas de message d'erreur associe au unlink pour cette raison
				unlink(".tmpheredoc");
			in = in->next;
		}
	}
	ft_in_lstclear(first_in);
	return (valid_in);
}

// parcourir la list d'outfiles. pour chacun, verifie les permissions ou cree
// selon simple ou double chevrons
// close tous les fd

int	check_out(t_redirect *out)
{
	int	fd;

	fd = 0;
	while (out)
	{
		if (access(out->path, F_OK) == 0 && access(out->path, W_OK) != 0)
		{
			print_str_fd("permission denied: ", out->path, 2);
			return (3);
		}
		else if (access(out->path, F_OK) != 0)
		{
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
		}
		out = out->next;
	}
	return (0);
}

t_redirect *get_valid_out(t_redirect *out)
{
	t_redirect *valid_out;
	t_redirect *first_out;

	first_out = out;
	valid_out = ft_in_lstlast(out);
	ft_in_lstclear(first_out);
	return (valid_out);
}

void print_str_fd(char *message, char *variable, int fd)
{
	ft_putstr_fd(message, fd);
	ft_putstr_fd(variable, fd);
	ft_putstr_fd("\n", fd);
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