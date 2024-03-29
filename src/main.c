/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:17:00 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/29 17:18:58 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "file_checks.h"
#include "env_parsing.h"
#include "exec.h"

int status_code;

void	ft_make_hist(void)
{
	add_history("chevron à la fin | fin<");
	add_history("chevron avant pipe < | fin");
	add_history("3 chevrons <<<infile | fin");
	add_history("3 chevrons >>>outfile | fin");
	add_history("pipe à la fin |");
	add_history("2 pipes à la suite | | fin");
	add_history("guillemet ' pas fermé");
	add_history("<<STOP <infile | grep <loremipsum >outfile la | cat >outfile");
	add_history("cat -e -n -s <<STOP <infile | grep <loremipsum >outfile la | cat >outfile");
}

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

static void	main_loop(t_persistent *pers)
{
	char	*read;
	t_cmd	*cmd;

	read = NULL;
	signals(1);
	read = get_read(pers->mini_env);
	if (!read)
	{
		ft_printf("exit\n");
		rl_clear_history();
		ft_freetab(pers->mini_env);
		exit (0);
	}
	if (read[0] != '\0')
	{
		cmd = parse_read(read, pers);
		if (!cmd)
			status_code = 1;
		if (cmd && !error_checks(cmd, pers->mini_env))
			status_code = exec(cmd, pers);
	}
}

int	main(int ac, char **av, char **env)
{
	t_persistent	persistent;

	ft_bzero(&persistent, sizeof(t_persistent));
	(void)av;
	if (ac > 1)
		return (ft_putstr_fd("Error\nminishell take no argument!\n", 2), 1);
	parse_env_array(&persistent, env);
	if (!persistent.mini_env)
		return (ft_putstr_fd("minishell: Cannot allocate memory\n", 2), 1);
	ft_make_hist();
	while (1)
		main_loop(&persistent);
	ft_freetab(persistent.mini_env);
	rl_clear_history();
	return (status_code);
}
