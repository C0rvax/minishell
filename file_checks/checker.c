/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:20:18 by ctruchot          #+#    #+#             */
/*   Updated: 2024/03/26 11:37:43 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_checks.h"
#include "minishell.h"

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

// checks through cmd list the outfiles.
// in case of error in some outfiles, kills the child.
// if all outfiles are OK, it only keeps the last one.
// return 1 in case of mistake in fd opening (strerror already displayed)

int	check_outfiles(t_cmd *cmd, int total_cmd, t_persistent *pers)
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
				kill_child(cmd, pers, 1);
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

// checks through cmd list the cmd path.
// if no argv[0], kills the child.
// checks if is a builtin and mark them as such
// returns 1 in case of malloc issue

int	check_cmd(t_cmd *cmd, int total_cmd, char **env, t_persistent *pers)
{
	int	cmd_nb;

	cmd_nb = 0;
	while (cmd_nb < total_cmd && cmd != NULL)
	{
		if (!cmd->argv || cmd->argv[0] == NULL)
			kill_child(cmd, pers, 0);
		if (cmd->type != KILLED)
		{
			if (check_builtins(cmd, total_cmd) != 0)
				return (0);
			if (get_cmd_path(cmd, env, pers) != 0)
				return (1);
		}
		cmd_nb++;
		cmd = cmd->next;
	}
	return (0);
}

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
