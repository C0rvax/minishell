/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_argument.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 19:53:41 by aduvilla          #+#    #+#             */
/*   Updated: 2024/04/17 12:52:42 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

static char	*check_in_env(char *arg, char **env)
{
	char	*value;
	int		i;
	int		len;

	i = 0;
	while (env[i])
	{
		len = ft_strlen(arg);
		if (ft_strnstr(env[i], arg, len) && env[i][len] == '=')
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

int	replace_in_list(char **read, char *arg, char *value, int index)
{
	char	*cpy;
	char	*cpy2;
	char	*new;
	size_t	index2;

	index2 = index + ft_strlen(arg) + 1;
	if (index == 0)
		cpy = ft_strdup("");
	else
		cpy = ft_substr(*read, 0, index);
	if (!cpy)
		return (msg_lex(MALLOC, 0, ""), 1);
	if (index2 == ft_strlen(*read))
		cpy2 = ft_strdup("");
	else
		cpy2 = ft_substr(*read, index2, ft_strlen(*read) - index2);
	if (!cpy2)
		return (free(cpy), msg_lex(MALLOC, 0, ""), 1);
	new = ft_trijoin(cpy, value, cpy2);
	if (!new)
		return (free(cpy), msg_lex(MALLOC, 0, ""), 1);
	cpy = *read;
	*read = new;
	free(cpy);
	return (0);
}

static int	find_and_replace(char **read, int *index, char **env)
{
	int		j;
	char	*arg;
	char	*value;

	j = *index + 1;
	while (ft_isalnum(read[0][j]) || read[0][j] == '_')
		j++;
	arg = ft_substr(*read, *index + 1, j - *index - 1);
	if (!arg)
		return (msg_lex(MALLOC, 0, ""), 1);
	if (arg[0] == '\0')
	{
		*index = *index + 1;
		return (free(arg), 0);
	}
	value = check_in_env(arg, env);
	if (!value)
		return (1);
	if (replace_in_list(read, arg, value, *index))
		return (free(arg), 1);
	free(arg);
	return (0);
}

static int	replace_status(char **read, int index, t_pers *pers)
{
	char		*arg;
	char		*value;

	arg = "?";
	if (g_status != 0)
	{
		pers->status_code = g_status;
		g_status = 0;
	}
	value = ft_itoa(pers->status_code);
	if (!value)
		return (msg_lex(MALLOC, 0, ""), 1);
	if (replace_in_list(read, arg, value, index))
		return (1);
	return (0);
}

int	replace_argument(char **read, t_pers *pers)
{
	int		i;
	int		dquote;
	char	**env;

	i = 0;
	dquote = 1;
	env = pers->mini_env;
	while (*read && read[0][i])
	{
		if (read[0][i] == 34)
			dquote *= -1;
		if (dquote > 0)
			pass_simple_quote(*read, &i);
		if (read[0][i] == '$' && read[0][i + 1] == '?'
			&& replace_status(read, i, pers))
			return (1);
		else if (read[0][i] == '$' && find_and_replace(read, &i, env))
			return (1);
		else if (read[0][i] == '~' && replace_home(pers, read, i))
			return (1);
		if (read[0][i] != '\0' && read[0][i] != '$')
			i++;
	}
	return (0);
}
