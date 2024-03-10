/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 13:07:55 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/10 15:53:25 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	count_argv(t_lst *lexer)
{
	int		i;
	t_lst	*buf;

	buf = lexer;
	i = 0;
	while (buf && buf->token != PIPE)
	{
		if (buf->token == CMD)
			i++;
		if (buf->token != CMD)
			i--;
		buf = buf->next;
	}
	return (i);
}

char	**create_arg_array(t_lst *lexer)
{
	t_lst	*buf;
	char	**argv;
	int		count;

	buf = lexer;
	count = count_argv(buf);
	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (ft_printf("Error: mallocarg1!\n"), NULL);
	count = 0;
	while (buf && buf->token != PIPE)
	{
		if (buf->token != CMD)
			buf = buf->next;
		else
		{
			argv[count] = ft_strdup(buf->str);
			if (!argv[count])
				return (ft_freetab(argv), ft_printf("Error: mallocarg2\n"), NULL);
			count++;
		}
		if (buf->next)
			buf = buf->next;
	}
	argv[count] = NULL;
	return (argv);
}

char	*find_last_token(t_lst *lexer, t_token token)
{
	int		i;
	int		j;
	char	*path;
	t_lst	*buf;

	i = 0;
	j = -1;
	buf = lexer;
	ft_printf("dans le find\n");
	while (buf && buf->token != PIPE)
	{
		if (buf->token == token)
			break ;
		i++;
		buf = buf->next;
	}
	ft_printf("dans le find\n");
	while (++j <= i && buf->next)
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
	t_lst	*buf;

	buf = lexer;
	if (cmd->in == SIMPLE)
	{
		cmd->infile = find_last_token(buf, IN);
		if (!cmd->infile)
			return (1);
	}
	if (cmd->in == DOUBLE)
	{
		cmd->infile = find_last_token(buf, DIN);
		if (!cmd->infile)
			return (1);
	}
	if (cmd->out == SIMPLE)
	{
		cmd->outfile = find_last_token(buf, OUT);
		if (!cmd->outfile)
			return (1);
	}
	if (cmd->out == DOUBLE)
	{
		cmd->outfile = find_last_token(buf, DOUT);
		if (!cmd->outfile)
			return (1);
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
	get_redirect_stat(buf, new);
	if (get_infile_outfile(new, buf))
		return (1);
	ft_cmd_lstadd_back(cmd, new);
	print_cmd_lst(*cmd);
	return (0);
}

void	create_cmd_list(t_parse *parse)
{
	t_lst	*lex;

	lex = parse->lexer;
	if (lex && lex->str)
	{
		ft_printf("dans le create\n");
		create_node_cmd(&parse->cmd, lex);
		while (lex && lex->token != PIPE)
			lex = lex->next;
		if (lex->next)
			lex = lex->next;
	}
}
