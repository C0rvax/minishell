/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:19:12 by aduvilla          #+#    #+#             */
/*   Updated: 2024/04/18 17:52:51 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"

static int	init_empty_env(t_pers *pers)
{
	char	*argv[4];
	char	**new;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (1);
	argv[0] = ft_strjoin("PWD=", pwd);
	free(pwd);
	if (!argv[0])
		return (1);
	argv[1] = "SHLVL=2";
	argv[2] = "_=/usr/bin/env";
	argv[3] = NULL;
	new = ft_joinarr(argv, pers->mini_env);
	free(argv[0]);
	if (!new)
		return (1);
	ft_freetab(pers->mini_env);
	pers->mini_env = new;
	return (0);
}

static int	get_lvl(char **env)
{
	int		ilvl;
	char	*slvl;

	slvl = ft_getenv(env, "SHLVL");
	if (!slvl || !slvl[0])
		return (0);
	ilvl = ft_atoi(slvl) + 1;
	free(slvl);
	return (ilvl);
}

static int	update_lvl(t_pers *pers)
{
	int		i;
	char	**new;
	char	*argv[3];
	char	*lvl;

	i = get_lvl(pers->mini_env);
	lvl = ft_itoa(i);
	if (!lvl)
		return (1);
	argv[0] = ft_strjoin("SHLVL=", lvl);
	free(lvl);
	if (!argv[0])
		return (1);
	argv[1] = "_=/usr/bin/env";
	argv[2] = NULL;
	new = ft_joinarr(argv, pers->mini_env);
	free(argv[0]);
	if (!new)
		return (1);
	ft_freetab(pers->mini_env);
	pers->mini_env = new;
	return (0);
}

int	init_env(t_pers *pers)
{
	if (!pers->mini_env || !pers->mini_env[0])
	{
		if (init_empty_env(pers))
			return (1);
	}
	else
	{
		if (update_lvl(pers))
			return (1);
	}
	return (0);
}
/*
static int	init_empty_env(t_pers *pers)
{
	char	*argv[4];
	char	**new;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (1);
	argv[0] = ft_strjoin("PWD=", pwd);
	free(pwd);
	if (!argv[0])
		return (1);
	argv[1] = ft_strdup("SHLVL=1");
	if (!argv[1])
		return (free(argv[0]), 1);
	argv[2] = ft_strdup("_=/usr/bin/env");
	if (!argv[2])
		return (free(argv[0]), free(argv[1]), 1);
	argv[3] = NULL;
	new = ft_joinarr(argv, pers->mini_env);
	if (!new)
		return (free(argv[0]), free(argv[1]), free(argv[2]), 1);
	ft_freetab(pers->mini_env);
	pers->mini_env = new;
	return (free(argv[0]), free(argv[1]), free(argv[2]), 0);
}
*/
