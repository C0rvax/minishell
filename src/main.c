/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:17:00 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/12 15:22:14 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "error_checks.h"


int	main(int ac, char **av, char **env)
{
	char	*read;
	t_cmd	*cmd;

	(void)av;
	if (ac > 1)
		return (ft_putstr_fd("Error\nminishell take no argument!\n", 2), 1);
	while (1)
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
		read = readline("minishell > ");
		cmd = parse_read(read, env);
		(void)cmd;
//		error_check(cmd); // changer le nom
		add_history(read);
		free(read);
	}
}
