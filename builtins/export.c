/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 19:33:18 by aduvilla          #+#    #+#             */
/*   Updated: 2024/04/02 17:23:38 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	print_env(t_exec *exec)
{
	int	i;
	int	fd;

	i = 0;
	fd = redirect_out(exec);
	if (fd < 0)
		return (clear_one(exec, msg_built(FD, exec->cmd->argv[1], 1)));
	if (exec->mini_env)
	{
		while (exec->mini_env[i])
		{
			ft_putstr_fd("declare -x ", fd);
			ft_putstr_fd(exec->mini_env[i], fd);
			ft_putstr_fd("\n", fd);
			i++;
		}
		if (fd != 1)
			close(fd);
	}
	return (0);
}

int	exec_export(t_exec *exec, t_persistent *pers)
{
	char	**new;
	char	**argv;
	char	**cpy;

	if (exec->total_cmd != 1)
		return (clear_one(exec, 0));
	argv = exec->cmd->argv;
	if (!argv[1])
		if (print_env(exec))
			return (1);
	cpy = exec->mini_env;
	new = ft_joinarr(argv, cpy);
	if (!new)
		return (clear_one(exec, msg_built(BMALLOC, argv[1], 1)));
	ft_freetab(cpy);
	pers->mini_env = new;
	return (clear_one(exec, 0));
}
