/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:17:00 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/13 14:54:03 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "file_checks.h"
#include "env_parsing.h"
#include "exec.h"


int	main(int ac, char **av, char **env)
{
	char	*read;
	t_cmd	*cmd;
	char	**mini_env;
	t_read	*read_list;

	read = NULL;
	read_list = NULL;
	(void)av;
	mini_env = parse_env_array(env);
	if (ac > 1)
		return (ft_putstr_fd("Error\nminishell take no argument!\n", 2), 1);
	mini_env = parse_env_array(env);
	while (1)
	{
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
		read = readline("minishell > ");
		if (read && read[0] != '\0')
		{
			cmd = parse_read(read, mini_env); // if !cmd gerer 
			if (error_checks(cmd, mini_env) != 0)
				return (ft_putstr_fd("\nSTOP\n", 2), 1);
			exec(cmd, mini_env);
		}
	}
}
