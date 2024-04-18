/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 19:33:18 by aduvilla          #+#    #+#             */
/*   Updated: 2024/04/18 14:52:29 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	exp_exp(t_exec *exec, t_pers *pers)
{
	char	**new;
	char	**argv;
	char	**cpy;

	argv = exec->cmd->argv;
	cpy = pers->export;
	new = ft_joinexp(argv, cpy);
	if (!new)
		return (clear_one(exec, msg_built(BMALLOC, argv[1], 1)));
	ft_freetab(cpy);
	pers->export = new;
	return (0);
}

static int	exp_env(t_exec *exec, t_pers *pers)
{
	char	**new;
	char	**argv;
	char	**cpy;

	argv = exec->cmd->argv;
	cpy = exec->mini_env;
	new = ft_joinarr(argv, cpy);
	if (!new)
		return (clear_one(exec, msg_built(BMALLOC, argv[1], 1)));
	ft_freetab(cpy);
	pers->mini_env = new;
	return (0);
}

static int	check_valid(char **argv)
{
	int		i;

	i = 1;
	while (argv[i])
	{
		if (arg_isok(argv[i]))
			return (1);
		i++;
	}
	return (0);
}

int	exec_export(t_exec *exec, t_pers *pers)
{
	char	**argv;
	int		status_code;

	status_code = 0;
	if (exec->total_cmd != 1)
		return (clear_one(exec, 0));
	argv = exec->cmd->argv;
	if (!argv[1])
	{
		if (print_export(exec, 1))
			return (1);
	}
	else
	{
		if (check_valid(argv))
			status_code = 1;
		if (exp_env(exec, pers))
			return (1);
		if (exp_exp(exec, pers))
			return (1);
	}
	return (clear_one(exec, status_code));
}
