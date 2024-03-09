/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_argument.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 19:53:41 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/09 19:56:51 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	check_line_argument(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 34)
		{
			i++;
			while (str[i] && str[i] != 34)
				i++;
		}
		if (str[i] && str[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

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
				exit(1);
			return (value);
		}
		i++;
	}
	value = malloc(1);
	if (!value)
		exit (1);
	value[0] = '\0';
	return (value);
}
/*
void	replace_in_list(t_lst *lst, char *arg, char *value, int index)
{
	char	*cpy;
	char	*newstring;
	int		i;
	int		len;
	int		size;

	i = -1;
	len = ft_strlen(value);
	cpy = lst->str;
	size = ft_strlen(cpy) - (ft_strlen(arg) + 1) + len; 
	newstring = malloc(sizeof(char) * (size + 1));
	while (++i < index)
		newstring[i] = cpy[i];
	index = index + ft_strlen(arg) + 1;
	while (len)
	{
		newstring[i + len - 1] = value[len - 1];
		len--;
	}
	i = i + ft_strlen(value);
	while (i < size)
	{
		newstring[i] = cpy[index];
		index++;
		i++;
	}
	lst->str = newstring;
	free(cpy);
}
*/

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
		cpy = ft_substr(lst->str, 0, index - 1);
	if (!cpy)
		return (1);
	if (index2 == ft_strlen(lst->str))
		cpy2 = ft_strdup("");
	else
		cpy2 = ft_substr(lst->str, index2, ft_strlen(lst->str) - index2);
	if (!cpy2)
		return (free(cpy), 1);
	new = ft_trijoin(cpy, value, cpy2);
	if (!new)
		exit (1);
	cpy = lst->str;
	lst->str = new;
	free(cpy);
	return (0);
}

static void	find_and_replace(t_lst *lst, int index, char **env)
{
	int		j;
	char	*arg;
	char	*value;

	j = index;
	while (lst->str[j] != '\0' && lst->str[j] != 34 && lst->str[j] != 39)
		j++;
	arg = ft_substr(lst->str, index + 1, j - index);
	if (!arg)
		exit(1);
	value = check_in_env(arg, env);
	if (value)
		replace_in_list(lst, arg, value, index);
	free(arg);
}

int	replace_argument(t_lst **lexer, char **env)
{
	t_lst	*buf;
	int		index;

	buf = *lexer;
	while (buf)
	{
		index = check_line_argument(buf->str);
		if (index >= 0)
			find_and_replace(buf, index, env);
		buf = buf->next;
	}
	return (0);
}
