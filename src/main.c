/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:17:00 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/20 20:13:15 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "file_checks.h"
#include "env_parsing.h"
#include "exec.h"

int	main(int ac, char **av, char **env)
{
	char			*read;
	t_cmd			*cmd;
	t_persistent	persistent;
	char			*prompt;

	read = NULL;
	(void)av;
	if (ac > 1)
		return (ft_putstr_fd("Error\nminishell take no argument!\n", 2), 1);
	persistent.mini_env = parse_env_array(env); // penser a free le mini_env !!!
	while (1)
	{
		prompt = get_prompt(persistent.mini_env); // penser a free le prompt !!!
		read = readline(prompt); // si ctrl-c free le prompt !!!
		free(prompt);
		if (read && read[0] != '\0')
		{
			cmd = parse_read(read, persistent.mini_env);
			if (cmd)
			{
				if (error_checks(cmd, persistent.mini_env) != 0) // je crois que la fonction return toujours 0
					return (ft_putstr_fd("\nSTOP\n", 2), 1); // si return alors free
				exec(cmd, persistent.mini_env);
			}
		}
	}
	ft_freetab(persistent.mini_env);
	rl_clear_history();
	return (0);
}
/*
		add_history("chevron à la fin | fin<");
		add_history("chevron avant pipe < | fin");
		add_history("3 chevrons <<<infile | fin");
		add_history("3 chevrons >>>outfile | fin");
		add_history("pipe à la fin |");
		add_history("2 pipes à la suite | | fin");
		add_history("guillemet ' pas fermé");
		add_history("<<STOP <infile | grep <loremipsum >outfile la | cat >outfile");
		add_history("cat -e -n -s <<STOP <infile | grep <loremipsum >outfile la | cat >outfile");
		*/
