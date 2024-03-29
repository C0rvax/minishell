/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_argument.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 19:53:41 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/29 17:23:48 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

extern int status_code;


static char	*check_in_env(char *arg, char **env)
{
	char	*value;
	int		i;
	int		len;

	i = 0;
	while (env[i])
	{
		len = ft_strlen(arg);
		if (ft_strnstr(env[i], arg, len))
		{
			value = ft_substr(env[i], len + 1, ft_strlen(env[i]) - (len + 1));
			if (!value)
				return (msg_lex(MALLOC, 0, ""), NULL);
			return (value);
		}
		i++;
	}
	value = malloc(1);
	if (!value)
		return (msg_lex(MALLOC, 0, ""), NULL);
	value[0] = '\0';
	return (value);
}

static int	replace_in_list(t_lst *lst, char *arg, char *value, int index)
{
	char	*cpy;
	char	*cpy2;
	char	*new;
	size_t	index2;

	index2 = index + ft_strlen(arg) + 1;
	if (index == 0)
		cpy = ft_strdup("");
	else
		cpy = ft_substr(lst->str, 0, index);
	if (!cpy)
		return (msg_lex(MALLOC, 0, ""), 1);
	if (index2 == ft_strlen(lst->str))
		cpy2 = ft_strdup("");
	else
		cpy2 = ft_substr(lst->str, index2, ft_strlen(lst->str) - index2);
	if (!cpy2)
		return (free(cpy), msg_lex(MALLOC, 0, ""), 1);
	new = ft_trijoin(cpy, value, cpy2);
	if (!new)
		return (free(cpy), msg_lex(MALLOC, 0, ""), 1);
	cpy = lst->str;
	lst->str = new;
	free(cpy);
	return (0);
}

static int	find_and_replace(t_lst *lst, int index, char **env)
{
	int		j;
	char	*arg;
	char	*value;

	j = index + 1;
	if (lst->str[j] == '\0')
		return (0);
	while (ft_isalnum(lst->str[j]) || lst->str[j] == '_')
		j++;
	arg = ft_substr(lst->str, index + 1, j - index - 1);
	if (!arg)
		return (msg_lex(MALLOC, 0, ""), 1);
	value = check_in_env(arg, env);
	if (!value)
		return (1);
	if (replace_in_list(lst, arg, value, index))
		return (free(arg), 1);
	free(arg);
	return (0);
}

static int	replace_status(t_lst *lst, int index)
{
	char	*arg;
	char	*value;

	arg = "?";
	value = ft_itoa(status_code);

	if (!value)
		return (msg_lex(MALLOC, 0, ""), 1);
	if (replace_in_list(lst, arg, value, index))
		return (1);
	return (0);
}

int	replace_argument(t_lst **lexer, t_persistent *pers)
{
	t_lst	*buf;
	int		i;

	buf = *lexer;
	while (buf)
	{
		i = 0;
		if (buf->token == DIN && buf->next)
			buf = buf->next->next;
		while (buf && buf->str[i])
		{
			pass_simple_quote(buf->str, &i);
			if (buf->str[i] == '$' && buf->str[i + 1] == '?'
				&& replace_status(buf, i/*, pers*/))
				return (1);
			if (buf->str[i] == '$' && find_and_replace(buf, i, pers->mini_env))
				return (1);
			if (buf->str[i] != '\0')
				i++;
		}
		if (buf)
			buf = buf->next;
	}
	return (0);
}
/*
int	replace_argument(t_lst **lexer, char **env)
{
	t_lst	*buf;
	int		i;

	buf = *lexer;
	while (buf)
	{
		i = 0;
		if (buf->token == DIN && buf->next)
			buf = buf->next->next;
		while (buf && buf->str[i])
		{
			pass_simple_quote(buf->str, &i);
			if (buf->str[i] == '$' && buf->str[i + 1] == '$'
				&& replace_dollar(buf, i, env))
				return (1);
			if (buf->str[i] == '$' && find_and_replace(buf, i, env))
				return (1);
			if (buf->str[i] != '\0')
				i++;
		}
		if (buf)
			buf = buf->next;
	}
	return (0);
}

static int	replace_dollar(t_lst *lst, int index, char **env)
{
	char	*value;

	value = check_in_env("SYSTEMD_EXEC_PID=", env);
	if (!value)
		return (1);
	if (replace_in_list(lst, "SYSTEMD_EXEC_PID=", value, index))
		return (1);
	return (0);
}
*/
