/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:38:44 by ctruchot          #+#    #+#             */
/*   Updated: 2024/03/11 16:38:00 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"
#include "error_checks.h"


int	ft_cmd_lstsize(t_cmd *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}

int error_check(t_cmd *cmd) 
{
	int total_cmd;
	int cmd_nb;
	
	total_cmd = ft_cmd_lstsize(cmd);
	cmd_nb = 0;
	while (cmd_nb < total_cmd) // parcourir les enfants ?
	{
		if (check_file(cmd->in) != 0)
			return 
		check_file(cmd->in, cmd_nb);
		cmd_nb++;
	}
	
}
// verifier les fichers infile et outfiles

int	ft_inout_lstsize(t_redirect *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}
// checks existence and rights on the files
int	check_in(t_redirect *cmd->in)
{
	// savoir la taille de cmd->in et verifier chaque node car 1 node = <in
	int size;
	size = ft_inout_lstsize;
	
	while (cmd->in->next) // parcourir la list d'infiles. pour chacun, access
	{
		if (cmd->in->mode == SIMPLE)
			check_file(cmd->in->path);
		if (cmd->in->mode == DOUBLE)
			// gerer heredoc
		cmd->in = cmd->in->next;
	}
}
	
int	check_infile(char *path)
{
	if (access(path, F_OK) != 0)
	{
		ft_putstr_fd("no such file or directory: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	if (access(path, F_OK) == 0 && access(path, R_OK) != 0)
	{
		ft_putstr_fd("permission denied: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
		return (2);
	}
	// if (cmd_nb != 0 && access(path, F_OK) == 0 && access(path, W_OK) != 0)
	// {
	// 	ft_putstr_fd("permission denied: ", 2);
	// 	ft_putstr_fd(path, 2);
	// 	ft_putstr_fd("\n", 2);
	// 	return (3);
	// }
	return (0);
}


int	parsing_infile(char **av, t_struc *data)
{
	char	*infile;

	infile = NULL;
	if (data->here_doc == true) // remplacer par cmd->
		infile = ft_strdup(".tmpheredoc");
	else
		infile = ft_strdup(av[1]);
	if (infile == NULL)
		return (1);
	if (check_file(infile, data->i) != 0)
		return (free(infile), 1);
	data->fdinfile = open(infile, O_RDONLY);
	if (data->fdinfile == -1)
		return (ft_putstr_fd(strerror(errno), 2), free(infile), 2);
	free(infile);
	return (0);
}

int	parsing_outfile(char **av, t_struc *data)
{
	char	*outfile;

	outfile = NULL;
	if (data->here_doc == true)
		outfile = ft_strdup(av[data->nbcmd + 3]);
	else
		outfile = ft_strdup(av[data->nbcmd + 2]);
	if (outfile == NULL)
		return (1);
	if (check_file(outfile, data->i) != 0)
		return (free(outfile), 1);
	if (data->here_doc == true)
		data->fdoutfile = open(outfile, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		data->fdoutfile = open(outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (data->fdoutfile == -1)
		return (ft_putstr_fd(strerror(errno), 2), free(outfile), 2);
	free(outfile);
	return (0);
}