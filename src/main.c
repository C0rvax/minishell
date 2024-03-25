/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:17:00 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/25 14:24:22 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "file_checks.h"
#include "env_parsing.h"
#include "exec.h"

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

int	main(int ac, char **av, char **env)
{
	char			*read;
	t_cmd			*cmd;
	t_persistent	persistent;
	char			*prompt;

	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	
	read = NULL;
	ft_bzero(&persistent, sizeof(t_persistent));
	(void)av;
	if (ac > 1)
		return (ft_putstr_fd("Error\nminishell take no argument!\n", 2), 1);
	parse_env_array(&persistent, env);
	if (!persistent.mini_env)
		return (ft_putstr_fd("Error\nminishell take no argument!\n", 2), 1);
	ft_make_hist();
	while (1)
	{
		read = get_read(persistent.mini_env);
		if (read && read[0] != '\0')
		{
			cmd = parse_read(read, persistent.mini_env);
			if (cmd && !error_checks(cmd, persistent.mini_env))
				persistent.status_code = exec(cmd, &persistent);
		}
	}
	ft_freetab(persistent.mini_env);
	rl_clear_history();
	return (persistent.status_code);
}
