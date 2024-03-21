/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:48:49 by ctruchot          #+#    #+#             */
/*   Updated: 2024/03/21 16:36:47 by ctruchot         ###   ########.fr       */
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
		if (!strncmp(builtarr[i], cmd->argv[0], ft_strlen(builtarr[i])))
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

int	exec_builtin_parent(t_exec *exec)
{
	int	i;

	i = is_a_builtin(exec->cmd);
	if (i == 0)
		exec_echo(exec);
	else if (i == 1)
		exec_cd(exec);
	else if (i == 2)
		exec_pwd(exec);
	else if (i == 3)
		exec_export(exec);
	else if (i == 4)
		exec_unset(exec);
	else if (i == 5)
		exec_env(exec);
	else if (i == 6)
		exec_exit_parent(exec);
	return (0);
}
