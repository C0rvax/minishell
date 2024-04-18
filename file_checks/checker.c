/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:20:18 by ctruchot          #+#    #+#             */
/*   Updated: 2024/04/18 17:41:10 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_checks.h"
#include "minishell.h"

// checks through cmd list the infiles.
// in case of error in some infiles, kills the child
// if no error is encountered, only keeps the last infile for exec.
// return (1) in case of error (malloc or fd error - errno already displayed)

static int	check_infiles(t_cmd *cmd, int total_cmd, t_pers *pers)
{
	int	cmd_nb;
	int	error;

	cmd_nb = 0;
	while (cmd_nb < total_cmd && cmd != NULL)
	{
		if (cmd->in)
		{
			error = check_in(cmd->in, pers);
			if (error == 0)
			{
				cmd->in = get_valid_in(cmd->in);
				if (!cmd->in)
					return (1);
			}
			else if (error == 2)
				return (1);
			else if (error == 1)
				if (kill_child(cmd, 1, pers, total_cmd) != 0)
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

static int	check_outfiles2(int error, t_cmd *cmd, int total_cmd, t_pers *pers)
{
	if (error == 0)
	{
		cmd->out = get_valid_out(cmd->out);
		if (!cmd->out)
			return (1);
		return (0);
	}
	else if (error == 2)
		return (1);
	else if (error == 1)
		if (kill_child(cmd, 1, pers, total_cmd) != 0)
			return (1);
	return (0);
}

static int	check_outfiles(t_cmd *cmd, int total_cmd, t_pers *pers)
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
			if (check_outfiles2(error, cmd, total_cmd, pers) == 1)
				return (1);
		}
		cmd_nb++;
		cmd = cmd->next;
	}
	return (0);
}

// checks through cmd list the cmd path. if no argv[0], kills the child.
// checks if is a builtin and mark them as such
// checks that the command is not a directory, returns 1 if it is and only child
// Then checks the path - get_cmd_path will return 1 or 2 if there is an issue
// or if no path is found and there was only one child -> return 1 to checker
// otherwise, whether there is a path or not, continues checking the commands
// status was updated through not_found

// returns 0 si builtin, si directory ds plusieurs enfants
// ou si path/pas path ds plusieurs enfants

// returns 1 only if is a directory and only child + issue
// or no path is found and only one child

static int	check_cmd(t_cmd *cmd, int total_cmd, char **env, t_pers *pers)
{
	int	cmd_nb;
	int	dir;

	cmd_nb = 0;
	dir = 0;
	while (cmd_nb < total_cmd && cmd != NULL)
	{
		if (!cmd->argv || !cmd->argv[0])
			kill_child(cmd, 0, pers, total_cmd);
		if (cmd->type != KILLED)
		{
			if (check_builtins(cmd, total_cmd) == 0)
			{
				dir = is_directory(cmd, pers, total_cmd);
				if (dir == 1)
					return (1);
				if (dir == 0)
					if (get_cmd_path(cmd, env, pers, total_cmd) != 0)
						return (1);
			}
		}
		cmd_nb++;
		cmd = cmd->next;
	}
	return (0);
}

// check errors in files and cmd
// checks all files in all cmd, then all outfiles in all cmd
// and finally all cmd

int	error_checks(t_cmd *cmd, char **mini_env, t_pers *pers)
{
	int	total_cmd;

	if (g_status == 130)
		g_status = 0;
	if (!cmd)
		return (1);
	total_cmd = ft_cmd_lstsize(cmd);
	if (total_cmd != 0)
	{
		if ((check_infiles(cmd, total_cmd, pers) != 0) || (check_outfiles(cmd,
					total_cmd, pers) != 0) || (check_cmd(cmd, total_cmd,
					mini_env, pers) != 0))
		{
			if (access("/tmp/.tmpheredoc", F_OK) == 0)
				unlink("/tmp/.tmpheredoc");
			ft_cmd_lstclear(&cmd);
			if (pers->status_code == 0)
				pers->status_code = 1;
			return (1);
		}
	}
	return (0);
}
