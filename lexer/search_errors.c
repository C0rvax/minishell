/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 13:04:58 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/26 14:44:40 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	search_parser_err(t_lst *list)
{
	t_lst	*buf;

	buf = list;
	while (buf)
	{
		if (buf->token != CMD && buf->token != PIPE)
		{
			if (buf->next == NULL)
				return (msg_lex(TOKEN, '\0', "newline"), 1);
			if (buf->next->token != CMD)
				return (msg_lex(TOKEN, buf->next->str[0], ""), 1);
		}
		if (buf->next && buf->token == PIPE && buf->next->token == PIPE)
			return (msg_lex(SPECIAL, 0, "||"), 1);
		buf = buf->next;
	}
	return (0);
}

void	msg_lex(t_msg msg, char c, char *str)
{
	if (msg == SPECIAL)
		ft_putstr_fd("minishell: our program do not handle special char ", 2);
	if (msg == TOKEN)
		ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	if (msg == QUOTE)
		ft_putstr_fd("minishell: close all quote or double quote", 2);
	if (msg == MALLOC)
		ft_putstr_fd("minishell: Cannot allocate memory", 2);
	if (msg == KILL)
		ft_putstr_fd("minishell: syntax error: unexpected end of file\nexit",
			2);
	if (c != '\0' || str[0])
	{
		ft_putchar_fd('\'', 2);
		ft_putchar_fd(c, 2);
		ft_putstr_fd(str, 2);
		ft_putchar_fd('\'', 2);
	}
	ft_putchar_fd('\n', 2);
}

int	append_new_read(char **read)
{
	char	*cpy;
	char	*read2;

	read2 = readline("> ");
	if (!read2)
		return (1);
	cpy = read[0];
	*read = ft_strjoin(cpy, read2);
	free(cpy);
	free(read2);
	if (!*read)
		return (msg_lex(MALLOC, 0, ""), 1);
	else
		return (0);
}

int	check_read(char **read)
{
	int	i;

	i = 0;
	if (!*read || *read[0] == '\0')
		return (1);
	while (read[0][i] != '\0')
	{
		if (pass_quote(*read, &i))
			return (msg_lex(QUOTE, '\0', ""), 1);
		if (is_special(read[0][i]))
			return (msg_lex(SPECIAL, read[0][i], ""), 1);
		if (read[0][i] == '$' && read[0][i + 1] == '$')
			return (msg_lex(SPECIAL, '\0', "$$"), 1);
		if (read[0][i] == '|' && read[0][i + 1] == '\0')
		{
			if (append_new_read(read))
				return (msg_lex(KILL, 0, ""), 2);
		}
		i++;
	}
	return (0);
}

int	search_errors(t_lst *list)
{
	if (search_parser_err(list))
		return (1);
	return (0);
}
