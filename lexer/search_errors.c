/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 13:04:58 by aduvilla          #+#    #+#             */
/*   Updated: 2024/04/09 11:45:04 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	msg_lex(t_msg msg, char c, char *str)
{
	if (msg == SPECIAL)
		ft_putstr_fd("minishell: not handled special char ", 2);
	if (msg == TOKEN)
		ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	if (msg == QUOTE)
		ft_putstr_fd("minishell: close the simple quote starting here: ", 2);
	if (msg == DQUOTE)
		ft_putstr_fd("minishell: close the double quote starting here: ", 2);
	if (msg == MALLOC)
		ft_putstr_fd("minishell: Cannot allocate memory", 2);
	if (msg == KILL)
		ft_putstr_fd("minishell: syntax error: unexpected end of file\nexit",
			2);
	if ((c != '\0' || str[0]) && msg != QUOTE && msg != DQUOTE)
	{
		ft_putchar_fd('\'', 2);
		ft_putchar_fd(c, 2);
		ft_putstr_fd(str, 2);
		ft_putchar_fd('\'', 2);
	}
	if (msg == QUOTE || msg == DQUOTE)
		ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
}

/************************************************************************/
/* 		check for unexpected token near the token after the one			*/
/* 		pointed by read[i]												*/
/************************************************************************/
static int	check_token(char *read, int i)
{
	if (read[i] == '<' || read[i] == '>')
	{
		i++;
		if (read[i] == read[i - 1])
			i++;
		while (read[i] == ' ')
			i++;
		if (!read[i])
			return (msg_lex(TOKEN, '\0', "newline"), 1);
		else if (is_token(read[i]))
			return (msg_lex(TOKEN, read[i], ""), 1);
		else
			return (0);
	}
	if (read[i] == '|')
	{
		while (read[i + 1] == ' ')
			i++;
		if (read[i + 1] == '|')
			return (msg_lex(TOKEN, read[i + 1], ""), 1);
		else
			return (0);
	}
	return (0);
}

/************************************************************************/
/* 		check for any syntax error in read								*/
/************************************************************************/
int	search_errors(char *read)
{
	int	i;

	i = 0;
	if (!read || read[0] == '\0')
		return (1);
	while (read[i])
	{
		if (read[0] == '|')
			return (msg_lex(TOKEN, read[0], ""), 1);
		if (pass_quote(read, &i))
			return (1);
		if (read[i] && is_special(read[i]))
			return (msg_lex(SPECIAL, read[i], ""), 1);
		if (read[i] == '$' && read[i + 1] == '$')
			return (msg_lex(SPECIAL, '\0', "$$"), 1);
		if (read[i] && check_token(read, i))
			return (1);
		i++;
	}
	return (0);
}
