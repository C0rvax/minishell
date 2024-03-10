/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:17:00 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/10 02:15:53 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

int	main(int ac, char **av, char **env)
{
	char	*read;

	(void)av;
	if (ac > 1)
		return (ft_putstr_fd("Error\nminishell take no argument!\n", 2), 1);
	while (1)
	{
		read = readline("minishell > ");
		parse_read(read, env);
		add_history(read);
		free(read);
	}
}
