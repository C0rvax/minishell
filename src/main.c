/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:17:00 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/12 21:31:33 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "file_checks.h"
#include "env_parsing.h"

int	main(int ac, char **av, char **env)
{
	char	*read;
	t_cmd	*cmd;
	char	**mini_env;

	(void)av;
	if (ac > 1)
		return (ft_putstr_fd("Error\nminishell take no argument!\n", 2), 1);
	while (1)
	{
		read = readline("minishell > ");
		mini_env = parse_env_array(env);
		cmd = parse_read(read, mini_env); // @Corvax, j'ai change env en mini_env - verifier que ca te creer pas de bug
		if (error_checks(cmd, mini_env) != 0)
			return (ft_printf("\nSTOP\n"), 1);
		
		add_history(read);
		free(read);
	}
}
