/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 13:07:55 by aduvilla          #+#    #+#             */
/*   Updated: 2024/04/16 17:45:05 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	add_redirect_node(t_cmd *cmd, char *str, t_mode mode, int inout)
{
	char		*cpy;
	t_redirect	*new;

	cpy = ft_strdup(str);
	if (!cpy)
		return (1);
	new = ft_redir_listnew(cpy, mode);
	if (!new)
		return (1);
	if (inout == 1)
		ft_redir_listadd_back(&cmd->in, new);
	else
		ft_redir_listadd_back(&cmd->out, new);
	return (0);
}

static int	get_list_infile(t_lst *lexer, t_cmd *cmd)
{
	t_lst		*buf;

	buf = lexer;
	while (buf && buf->token != PIPE)
	{
		if (buf->token == IN && buf->next)
		{
			if (add_redirect_node(cmd, buf->next->str, SIMPLE, 1))
				return (1);
		}
		else if (buf->token == DIN && buf->next)
		{
			if (add_redirect_node(cmd, buf->next->str, DOUBLE, 1))
				return (1);
		}
		buf = buf->next;
	}
	return (0);
}

static int	get_list_outfile(t_lst *lexer, t_cmd *cmd)
{
	t_lst		*buf;

	buf = lexer;
	while (buf && buf->token != PIPE)
	{
		if (buf->token == OUT && buf->next)
		{
			if (add_redirect_node(cmd, buf->next->str, SIMPLE, 2))
				return (1);
		}
		else if (buf->token == DOUT && buf->next)
		{
			if (add_redirect_node(cmd, buf->next->str, DOUBLE, 2))
				return (1);
		}
		buf = buf->next;
	}
	return (0);
}

int	create_node_cmd(t_cmd **cmd, t_lst *lexer)
{
	char	**argv;
	t_lst	*buf;
	t_cmd	*new;

	buf = lexer;
	argv = create_arg_array(buf);
	if (!argv)
		return (1);
	new = ft_cmd_lstnew(argv);
	if (!new)
		return (1);
	if (get_list_infile(buf, new))
		return (1);
	if (get_list_outfile(buf, new))
		return (1);
	ft_cmd_lstadd_back(cmd, new);
	return (0);
}

int	create_cmd_list(t_parse *parse)
{
	t_lst	*lex;

	lex = parse->lexer;
	while (lex && lex->str)
	{
		if (create_node_cmd(&parse->cmd, lex))
			return (1);
		while (lex && lex->token != PIPE)
			lex = lex->next;
		if (lex)
			lex = lex->next;
	}
	return (0);
}
