/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:17:00 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/09 15:21:13 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

void	print_lst(t_lst *lexer)
{
	int	i;

	i = 0;
	if (lexer)
	{
		while (lexer)
		{
			ft_printf("str[%d] = %s\n", i, lexer->str);
			lexer = lexer->next;
			i++;
		}
	}
}

int	main(int ac, char **av, char **env)
{
	char	*read;
	t_lst	*lexer;
//  t_data	data;

	(void)env;
	(void)av;
	lexer = NULL;
	if (ac > 1)
		return (ft_putstr_fd("Error\nminishell take no argument!\n", 2), 1);
	while (1)
	{
		read = readline("minishell > ");
		count_token(&lexer, read);
		print_lst(lexer);
//		parse_line(read);
	}

}
