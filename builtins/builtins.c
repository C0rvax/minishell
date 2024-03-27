/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:48:49 by ctruchot          #+#    #+#             */
/*   Updated: 2024/03/27 17:04:32 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	is_a_builtin(t_cmd *cmd)
{
	char	*str;
	char	**builtarr;
	int		i;

	i = 0;
	str = "echo;cd;pwd;export;unset;env;exit";
	builtarr = ft_split(str, ';');
	if (!builtarr)
		return (-2);
	while (builtarr[i])
	{
		if (!strncmp(builtarr[i], cmd->argv[0], ft_strlen(builtarr[i]) + 1))
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
		exec_cd_c(exec, child);
	else if (i == 2)
		exec_pwd_c(exec, child);
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

int	exec_builtin_parent(t_exec *exec, t_persistent *pers)
{
	int	i;
	int	status_code;

	status_code = 0;
	i = is_a_builtin(exec->cmd);
	if (i == 0)
		status_code = exec_echo(exec);
	else if (i == 1)
		status_code = exec_cd(exec);
	else if (i == 2)
		status_code = exec_pwd(exec);
	else if (i == 3)
		status_code = exec_export(exec, pers);
	else if (i == 4)
		status_code = exec_unset(exec, pers);
	else if (i == 5)
		status_code = exec_env(exec);
	else if (i == 6)
		exec_exit_parent(exec);
	return (status_code);
}
