/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 13:07:55 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/11 18:00:47 by aduvilla         ###   ########.fr       */
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

void	create_cmd_list(t_parse *parse)
{
	t_lst	*lex;

	lex = parse->lexer;
	while (lex && lex->str)
	{
		create_node_cmd(&parse->cmd, lex);
		while (lex && lex->token != PIPE)
			lex = lex->next;
		if (lex && lex->next)
			lex = lex->next;
	}
}
/*
char	*find_last_token(t_lst *lexer, t_token token)
{
	int		i;
	int		j;
	char	*path;
	t_lst	*buf;

	i = 0;
	j = 0;
	buf = lexer;
	while (buf && buf->token != PIPE)
	{
		if (buf->token == token)
			j = i;
		i++;
		buf = buf->next;
	}
	i = -1;
	buf = lexer;
	while (++i <= j && buf->next)
		buf = buf->next;
	path = ft_strdup(buf->str);
	if (!path)
		return (ft_printf("Error: mallocpath!\n"), NULL);
	return (path);
}

void	get_redirect_stat(t_lst *lexer, t_cmd *cmd)
{
	t_lst	*buf;

	buf = lexer;
	cmd->in = NONE;
	cmd->out = NONE;
	while (buf && buf->token != PIPE)
	{
		if (buf->token == IN)
			cmd->in = SIMPLE;
		if (buf->token == OUT)
			cmd->out = SIMPLE;
		if (buf->token == DIN)
			cmd->in = DOUBLE;
		if (buf->token == DOUT)
			cmd->out = DOUBLE;
		buf = buf->next;
	}
}

int	get_infile_outfile(t_cmd *cmd, t_lst *lexer)
{
	if (cmd->in == SIMPLE)
	{
		cmd->infile = find_last_token(lexer, IN);
		if (!cmd->infile)
			return (1);
	}
	if (cmd->in == DOUBLE)
	{
		cmd->infile = find_last_token(lexer, DIN);
		if (!cmd->infile)
			return (1);
	}
	if (cmd->out == SIMPLE)
	{
		cmd->outfile = find_last_token(lexer, OUT);
		if (!cmd->outfile)
			return (1);
	}
	if (cmd->out == DOUBLE)
	{
		cmd->outfile = find_last_token(lexer, DOUT);
		if (!cmd->outfile)
			return (1);
	}
	return (0);
}
*/
