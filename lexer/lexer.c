/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:00:25 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/10 02:09:10 by aduvilla         ###   ########.fr       */
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

static int	create_node_out(t_lst *list, char *read, int i, int *j)
{
	t_lst	*new;

	if (i > 0 && read[i - 1] == '>')
		return (0);
	if (read[i + 1] == '>')
	{
		new = ft_listnew(ft_strdup(">>"), DOUT);
		ft_listadd_back(&list, new);
		if (read[i + 2] == '>')
			return (ft_printf("wrong\n"), 1);
		*j = i + 2;
	}
	else
	{
		new = ft_listnew(ft_strdup(">"), OUT);
		ft_listadd_back(&list, new);
		*j = i + 1;
	}
	return (0);
}

static int	create_node_in(t_lst *list, char *read, int i, int *j)
{
	t_lst	*new;

	if (i > 0 && read[i - 1] == '<')
		return (0);
	if (read[i + 1] == '<')
	{
		new = ft_listnew(ft_strdup("<<"), DIN);
		ft_listadd_back(&list, new);
		if (read[i + 2] == '<')
			return (ft_printf("bash: syntax error near unexpected tok\n"), 1);
		*j = i + 2;
	}
	else
	{
		new = ft_listnew(ft_strdup("<"), IN);
		ft_listadd_back(&list, new);
		*j = i + 1;
	}
	return (0);
}

static int	create_list_node(t_lst **list, char *read, int i, int *j)
{
	t_lst	*new;
	char	*sub;
	int		res;

	res = 0;
	if (i > *j)
	{
		sub = ft_substr(read, *j, i - *j);
		if (!sub)
			return (1);
		new = ft_listnew(sub, CMD);
		ft_listadd_back(list, new);
	}
	if (read[i] == '|')
		create_node_pipe(*list, i, j);
	if (read[i] == '>')
		res = create_node_out(*list, read, i, j);
	if (read[i] == '<')
		res = create_node_in(*list, read, i, j);
	if (read[i] == ' ')
		*j = i + 1;
	if (read[i] == '$')
		*j = i;
	return (res);
}

int	create_token_list(t_lst **lexer, char *read)
{
	int	i;
	int	j;
	int	res;

	i = 0;
	j = 0;
	res = 0;
	while (read && read[i])
	{
		pass_quote(read, &i);
		if (read[i] && is_token(read[i]))
			res = create_list_node(lexer, read, i, &j);
		if (res)
			return (res);
		i++;
	}
	res = create_list_node(lexer, read, i, &j);
	return (res);
}
