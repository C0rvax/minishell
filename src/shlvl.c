/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:31:53 by aduvilla          #+#    #+#             */
/*   Updated: 2024/04/18 11:21:30 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	update_lvl(t_exec *exec, t_pers *pers, int sign)
{
	int		i;
	char	**new;
	char	*argv[2];
	char	*lvl;


	i = ft_atoi(ft_getenv(pers->mini_env, "SHLVL"));
	i = i + sign;
	lvl = ft_itoa(i);
	if (!lvl)
		return (1);
	argv[0] = ft_strjoin("SHLVL=", lvl);
	free(lvl);
	if (!argv[0])
		return (1);
	argv[1] = NULL;
	new = ft_joinarr(argv, pers->mini_env);
	free(argv[0]);
	if (!new)
		return (1);
	ft_freetab(pers->mini_env);
	pers->mini_env = new;
	exec->mini_env = new;
	return (0);
}

static int	is_a_shell(char *str)
{
	int		size;

	if (access(str, F_OK | X_OK) == 0)
	{
		size = ft_strlen(str);
		if (size - 11 >= 0 && !ft_strcmp(&str[size - 11], "./minishell"))
			return (1);
		else if (size - 4 >= 0 && !ft_strcmp(&str[size - 4], "bash"))
			return (1);
		else if (size - 3 >= 0 && !ft_strcmp(&str[size - 4], "zsh"))
			return (1);
	}
	return (0);
}
