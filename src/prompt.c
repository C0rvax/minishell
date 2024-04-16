/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:08:24 by aduvilla          #+#    #+#             */
/*   Updated: 2024/04/16 17:38:07 by aduvilla         ###   ########.fr       */
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

static char	*get_sess(char **env)
{
	char	*sess;
	char	*session;
	int		i;
	int		j;

	i = 0;
	j = 0;
	sess = ft_getenv(env, "SESSION_MANAGER");
	if (!sess)
	{
		ft_putstr_fd(strerror(errno), 2);
		return (NULL);
	}
	while (sess[i] && sess[i] != '/')
		i++;
	while (sess[i + j] && sess[i + j] != '.')
		j++;
	session = ft_substr(sess, i + 1, j - 1);
	return (free(sess), session);
}

static char	*get_path(char **env)
{
	char	*path_raw;
	char	*path;
	char	*pwd;
	char	*home;
	size_t	i;

	home = ft_getenv(env, "HOME");
	if (!home)
		return (NULL);
	pwd = ft_getenv(env, "PWD");
	if (!pwd)
		return (free(home), NULL);
	i = ft_strlen(home);
	path_raw = ft_substr(pwd, i, ft_strlen(pwd) - i);
	if (!path_raw)
		return (free(pwd), free(home), NULL);
	path = malloc(sizeof(char) * (ft_strlen(path_raw) + 2));
	if (!path)
		return (free(pwd), free(home), free(path_raw), NULL);
	i = 0;
	path[0] = '~';
	while (++i < ft_strlen(path_raw) + 1)
		path[i] = path_raw[i - 1];
	path[i] = '\0';
	return (free(pwd), free(home), free(path_raw), path);
}

char	*get_prompt(char **env)
{
	char	*user;
	char	*session;
	char	*path;
	char	*prompt;

	user = ft_getenv(env, "USER");
	if (!user)
		return (NULL);
	session = get_sess(env);
	if (!session)
		return (free(user), NULL);
	path = get_path(env);
	if (!user || !session || !path)
		prompt = ft_strdup("minishell$ ");
	else
		prompt = mix_all(user, session, path);
	return (free(user), free(path), free(session), prompt);
}
