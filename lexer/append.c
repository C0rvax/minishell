/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:11:39 by aduvilla          #+#    #+#             */
/*   Updated: 2024/04/18 15:14:20 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

static void	exit_parse(t_pers *pers, char *read)
{
	free(read);
	ft_putstr_fd("\nminishell: syntax error: unexpected end of file\n", 2);
	ft_printf("exit\n");
	ft_freetab(pers->mini_env);
	ft_freetab(pers->export);
	rl_clear_history();
	exit(2);
}

static int	last_ispipe(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len >= 1)
		len--;
	while (str[len] == ' ')
		len--;
	if (str[len] == '|')
		return (1);
	else
		return (0);
}

static int	append_new(char **read, t_pers *pers)
{
	char	*cpy;
	char	*read2;

	read2 = prompted_gnl("> ", 0, 2);
	if (!read2 && g_status != 130)
		exit_parse(pers, *read);
	if (g_status == 130)
	{
		pers->status_code = 130;
		g_status = 0;
		return (add_history(*read), free(read2), free(*read), 1);
	}
	cpy = read[0];
	*read = ft_strjoin(cpy, read2);
	free(read2);
	if (!*read)
		return (add_history(cpy), free(cpy), msg_lex(MALLOC, 0, ""), 1);
	free(cpy);
	if (search_errors(*read))
		return (add_history(*read), free(*read), 2);
	return (0);
}

int	append_new_read(char **read, t_pers *pers)
{
	int	len;

	if (search_errors(*read))
	{
		pers->status_code = 2;
		g_status = 0;
		return (add_history(*read), free(*read), 1);
	}
	len = ft_strlen(read[0]);
	while (len > 0 && last_ispipe(*read))
	{
		pers->status_code = append_new(read, pers);
		if (pers->status_code)
		{
			g_status = 0;
			return (1);
		}
	}
	return (0);
}
