/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:00:25 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/29 17:15:29 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

extern int status_code;

static int	create_node_pipe(t_lst *list, int i, int *j)
{
	t_lst	*new;

	new = NULL;
	new = ft_listnew(ft_strdup("|"), PIPE);
	if (!new)
		return (msg_lex(MALLOC, '\0', ""), 1);
	ft_listadd_back(&list, new);
	*j = i + 1;
	return (0);
}

static int	create_node_out(t_lst **list, char *read, int i, int *j)
{
	t_lst	*new;

	new = NULL;
	if (i > 0 && read[i - 1] == '>')
		return (0);
	if (read[i + 1] == '>')
	{
		new = ft_listnew(ft_strdup(">>"), DOUT);
		if (read[i + 2] == '>')
			return (msg_lex(TOKEN, read[i + 2], ""), 1);
		*j = i + 2;
	}
	else
	{
		new = ft_listnew(ft_strdup(">"), OUT);
		*j = i + 1;
	}
	if (!new)
		return (msg_lex(MALLOC, '\0', ""), 1);
	ft_listadd_back(list, new);
	return (0);
}

static int	create_node_in(t_lst **list, char *read, int i, int *j)
{
	t_lst	*new;

	new = NULL;
	if (i > 0 && read[i - 1] == '<')
		return (0);
	if (read[i + 1] == '<')
	{
		new = ft_listnew(ft_strdup("<<"), DIN);
		if (read[i + 2] == '<')
			return (msg_lex(TOKEN, read[i + 2], ""), 1);
		*j = i + 2;
	}
	else
	{
		new = ft_listnew(ft_strdup("<"), IN);
		*j = i + 1;
	}
	if (!new)
		return (msg_lex(MALLOC, '\0', ""), 1);
	ft_listadd_back(list, new);
	return (0);
}

static int	create_list_node(t_lst **list, char *read, int i, int *j)
{
	t_lst	*new;
	int		x;

	x = 0;
	if (i > *j)
	{
		new = ft_listnew(ft_substr(read, *j, i - *j), CMD);
		if (!new)
			return (msg_lex(MALLOC, '\0', ""), 1);
		ft_listadd_back(list, new);
	}
	if (read[i] == '|')
		x = create_node_pipe(*list, i, j);
	if (read[i] == '>')
		x = create_node_out(list, read, i, j);
	if (read[i] == '<')
		x = create_node_in(list, read, i, j);
	if (read[i] == ' ')
		*j = i + 1;
	return (x);
}

int	create_token_list(t_lst **lexer, char *read)
{
	int	i;
	int	j;
	int	x;

	i = 0;
	j = 0;
	x = 0;
	while (read && read[i])
	{
		pass_quote(read, &i);
		if (read[i] && is_token(read[i]))
			x = create_list_node(lexer, read, i, &j);
		if (x)	
			return (x);
		i++;
	}
	x = create_list_node(lexer, read, i, &j);
	return (x);
}
