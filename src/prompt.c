/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:08:24 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/16 15:27:03 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*mix_all(char *user, char *session, char *path)
{
	int		i;
	int		lenu;
	int		lens;
	int		lenp;
	char	*prompt;

	lenu = ft_strlen(user);
	lens = ft_strlen(session);
	lenp = ft_strlen(path);
	prompt = malloc(sizeof(char) * (lenu + lens + lenp + 5));
	if (!prompt)
		return (NULL);
	i = -1;
	while (++i < lenu)
		prompt[i] = user[i];
	prompt[i] = '@';
	while (++i < lenu + lens + 1)
		prompt[i] = session[i - lenu - 1];
	prompt[i] = ':';
	while (++i < lenu + lens + lenp + 2)
		prompt[i] = path[i - lenu - lens - 2];
	prompt[i] = '$';
	prompt[++i] = ' ';
	prompt[++i] = '\0';
	return (prompt);
}

static char	*get_sess(void)
{
	char	*sess;
	char	*session;
	int		i;
	int		j;

	i = 0;
	j = 0;
	sess = getenv("SESSION_MANAGER");
	if (!sess)
		return (NULL);
	while (sess[i] && sess[i] != '/')
		i++;
	while (sess[i + j] && sess[i + j] != '.')
		j++;
	session = ft_substr(sess, i + 1, j - 1);
	return (session);
}

static char	*get_path(void)
{
	char	*path_raw;
	char	*path;
	char	*pwd;
	char	*home;
	size_t	i;

	pwd = getenv("PWD");
	home = getenv("HOME");
	if (!pwd || !home)
		return (NULL);
	path_raw = ft_substr(pwd, ft_strlen(home),
			ft_strlen(pwd) - ft_strlen(home));
	path = malloc(sizeof(char) * (ft_strlen(path_raw) + 2));
	if (!path)
		return (free(path_raw), NULL);
	i = 0;
	path[0] = '~';
	while (i < ft_strlen(path_raw))
	{
		path[i + 1] = path_raw[i];
		i++;
	}
	path[i + 1] = '\0';
	return (free(path_raw), path);
}

char	*get_prompt(void)
{
	char	*user;
	char	*session;
	char	*path;
	char	*prompt;

	user = getenv("USER");
	session = get_sess();
	path = get_path();
	if (!user || !session || !path)
		prompt = ft_strdup("minishell$ ");
	else
		prompt = mix_all(user, session, path);
	if (!prompt)
		return (free(path), free(session), NULL);
	return (free(path), free(session), prompt);
}
