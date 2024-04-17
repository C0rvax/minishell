/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:17:00 by aduvilla          #+#    #+#             */
/*   Updated: 2024/04/17 17:38:29 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"
#include "lexer.h"
#include "file_checks.h"
#include "exec.h"

int	g_status = 0;

static char	*get_read(char **env)
{
	char	*prompt;
	char	*read;

	prompt = get_prompt(env);
	if (!prompt)
		read = readline("minishell$ ");
	else
	{
		read = readline(prompt);
		free(prompt);
	}
	return (read);
}

static void	main_loop(t_pers *pers)
{
	char		*read;
	t_cmd		*cmd;

	read = NULL;
	signals(1);
	read = get_read(pers->mini_env);
	if (!read)
	{
		ft_printf("exit\n");
		rl_clear_history();
		ft_freetab(pers->mini_env);
		ft_freetab(pers->export);
		exit (0);
	}
	if (read[0] != '\0')
	{
		cmd = parse_read(read, pers);
		if (!cmd && pers->status_code != 130 && pers->status_code != 2)
			pers->status_code = 1;
		if (cmd && !error_checks(cmd, pers->mini_env, pers))
			pers->status_code = exec(cmd, pers);
	}
}

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

static int	init_env(t_pers *pers)
{
	char	*argv[2];
	char	**new;

	if (!pers->mini_env || !pers->mini_env[0])
	{
		if (init_empty_env(pers))
			return (1);
	}
	else
	{
		argv[0] = "_=/usr/bin/env";
		argv[1] = NULL;
		new = ft_joinarr(argv, pers->mini_env);
		if (!new)
			return (1);
		ft_freetab(pers->mini_env);
		pers->mini_env = new;
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_pers	persistent;

	ft_bzero(&persistent, sizeof(t_pers));
	(void)av;
	if (ac > 1)
		return (ft_putstr_fd("Error\nminishell take no argument!\n", 2), 1);
	parse_env_array(&persistent, env);
	if (!persistent.mini_env)
		return (ft_putstr_fd("minishell: Cannot allocate memory\n", 2), 1);
	if (init_env(&persistent))
	{
		ft_freetab(persistent.mini_env);
		return (ft_putstr_fd("minishell: Cannot allocate memory\n", 2), 1);
	}
	while (1)
		main_loop(&persistent);
	ft_freetab(persistent.mini_env);
	ft_freetab(persistent.export);
	rl_clear_history();
	return (persistent.status_code);
}
