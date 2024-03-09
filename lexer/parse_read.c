/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:23:28 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/09 19:57:02 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	parse_read(char *read, char **env)
{
	t_parse	data;

	data.lexer = NULL;
	if (!read)
		return (1);
	create_token_list(&data.lexer, read);
	replace_argument(&data.lexer, env);
	print_lst(data.lexer);
	ft_listclear(&data.lexer);
	return (0);
}
