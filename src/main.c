/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:17:00 by aduvilla          #+#    #+#             */
/*   Updated: 2024/04/18 15:14:27 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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
		if (!cmd && pers->status_code == -1)
			pers->status_code = 0;
		else if (!cmd && pers->status_code != 130 && pers->status_code != 2)
			pers->status_code = 1;
		else if (cmd && !error_checks(cmd, pers->mini_env, pers))
			pers->status_code = exec(cmd, pers);
	}
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
