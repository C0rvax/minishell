/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:00:25 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/09 19:46:04 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	create_node_pipe(t_lst *list, int i, int *j)
{
	t_lst	*new;

	new = ft_listnew(ft_strdup("|"), PIPE);
	ft_listadd_back(&list, new);
	*j = i + 1;
}

static void	create_node_out(t_lst *list, char *read, int i, int *j)
{
	t_lst	*new;

	if (i > 0 && read[i - 1] == '>')
		return ;
	if (read[i + 1] == '>')
	{
		new = ft_listnew(ft_strdup(">>"), DOUT);
		ft_listadd_back(&list, new);
		while (read[i] == '>')
			i++;
		*j = i;
	}
	else
	{
		new = ft_listnew(ft_strdup(">"), OUT);
		ft_listadd_back(&list, new);
		*j = i + 1;
	}
}

static void	create_node_in(t_lst *list, char *read, int i, int *j)
{
	t_lst	*new;

	if (i > 0 && read[i - 1] == '<')
		return ;
	if (read[i + 1] == '<')
	{
		new = ft_listnew(ft_strdup("<<"), DIN);
		ft_listadd_back(&list, new);
		while (read[i] == '<')
			i++;
		*j = i;
	}
	else
	{
		new = ft_listnew(ft_strdup("<"), IN);
		ft_listadd_back(&list, new);
		*j = i + 1;
	}
}

static void	create_list_node(t_lst **list, char *read, int i, int *j)
{
	t_lst	*new;
	char	*sub;

	if (i > *j)
	{
		sub = ft_substr(read, *j, i - *j);
		if (!sub)
			exit (1);
		new = ft_listnew(sub, CMD);
		ft_listadd_back(list, new);
	}
	if (read[i] == '|')
		create_node_pipe(*list, i, j);
	if (read[i] == '>')
		create_node_out(*list, read, i, j);
	if (read[i] == '<')
		create_node_in(*list, read, i, j);
	if (read[i] == ' ')
		*j = i + 1;
}

void	create_token_list(t_lst **lexer, char *read)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (read && read[i])
	{
		if (read[i] && read[i] == 39)
		{
			i++;
			while (read[i] && read[i] != 39)
				i++;
		}
		if (read[i] && read[i] == 34)
		{
			i++;
			while (read[i] && read[i] != 34)
				i++;
		}
		if (read[i] && is_token(read[i]))
			create_list_node(lexer, read, i, &j);
		i++;
	}
	create_list_node(lexer, read, i, &j);
}
