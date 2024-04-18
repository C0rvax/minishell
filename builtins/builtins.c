/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:48:49 by ctruchot          #+#    #+#             */
/*   Updated: 2024/04/18 17:19:32 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	is_a_builtin(t_cmd *cmd)
{
	char	*builtstr;
	char	*str;
	char	**builtarr;
	int		i;

	str = cmd->argv[0];
	i = 0;
	builtstr = "echo;cd;pwd;export;unset;env;exit";
	builtarr = ft_split(builtstr, ';');
	if (!builtarr)
		return (-2);
	while (builtarr[i])
	{
		if (!ft_strncmp(builtarr[i], str, ft_strlen(builtarr[i]) + 1))
			return (ft_freetab(builtarr), i);
		i++;
	}
	return (ft_freetab(builtarr), -1);
}

int	exec_builtin(t_exec *exec, t_child *child)
{
	int	i;

	i = is_a_builtin(child->current_cmd);
	if (i == 0)
		exec_echo_c(exec, child);
	else if (i == 1)
		clear_built(exec, child, 0);
	else if (i == 2)
		exec_pwd_c(exec, child);
	else if (i == 3 && !child->current_cmd->argv[1])
		print_export(exec, 2);
	else if (i == 3)
		clear_built(exec, child, 0);
	else if (i == 4)
		clear_built(exec, child, 0);
	else if (i == 5)
		exec_env_c(exec, child);
	else if (i == 6)
		exec_exit_c(exec, child);
	return (0);
}

int	redirect_out(t_exec *exec)
{
	int	fd;

	if (exec->cmd->out && exec->cmd->out->mode == SIMPLE)
		fd = open(exec->cmd->out->path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (exec->cmd->out && exec->cmd->out->mode == DOUBLE)
		fd = open(exec->cmd->out->path, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		fd = 1;
	return (fd);
}

int	exec_builtin_parent(t_exec *exec, t_pers *pers)
{
	int			i;

	i = is_a_builtin(exec->cmd);
	if (i == 0)
		pers->status_code = exec_echo(exec);
	else if (i == 1)
		pers->status_code = exec_cd(exec, pers);
	else if (i == 2)
		pers->status_code = exec_pwd(exec);
	else if (i == 3)
		pers->status_code = exec_export(exec, pers);
	else if (i == 4)
		pers->status_code = exec_unset(exec, pers);
	else if (i == 5)
		pers->status_code = exec_env(exec);
	else if (i == 6)
		exec_exit_parent(exec, pers);
	return (pers->status_code);
}
