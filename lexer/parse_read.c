/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:23:28 by aduvilla          #+#    #+#             */
/*   Updated: 2024/04/11 17:30:15 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

static void	sig_parse(void)
{
	struct sigaction	parsig;

	sigemptyset(&parsig.sa_mask);
	parsig.sa_handler = &handle_sigint_read;
	parsig.sa_flags = 0;
	sigaction(SIGINT, &parsig, NULL);
}

static void	exit_parse(t_persistent *pers, char *read)
{
	free(read);
	ft_putstr_fd("minishell: syntax error: unexpected end of file\n", 2);
	ft_printf("exit\n");
	ft_freetab(pers->mini_env);
	ft_freetab(pers->export);
	rl_clear_history();
	exit (0);
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

static int	append_new_read(char **read, t_persistent *pers)
{
	char	*cpy;
	char	*read2;
	int		len;

	if (search_errors(*read))
		return (add_history(*read), free(*read), 1);
	len = ft_strlen(read[0]);
	while (len > 0 && last_ispipe(*read))
	{
		read2 = prompted_gnl("> ", 0, 2);
		if (!read2 && g_status != 130)
			exit_parse(pers, *read);
		if (g_status == 130)
			return (add_history(*read), free(read2), free(*read), 1);
		cpy = read[0];
		*read = ft_strjoin(cpy, read2);
		free(read2);
		if (!*read)
			return (add_history(cpy), free(cpy), msg_lex(MALLOC, 0, ""), 1);
		free(cpy);
		if (search_errors(*read))
			return (add_history(*read), free(*read), 1);
		len = ft_strlen(read[0]);
	}
	return (0);
}

t_cmd	*parse_read(char *read, t_persistent *pers)
{
	t_parse	parse;

	sig_parse();
	ft_bzero(&parse, sizeof(t_parse));
	if (!read || read[0] == '\0')
		return (NULL);
	if (append_new_read(&read, pers))
		return (NULL);
	add_history(read);
	if (replace_argument(&read, pers))
		return (ft_listclear(&parse.lexer), NULL);
	if (create_token_list(&parse.lexer, read))
		return (free(read), ft_listclear(&parse.lexer), NULL);
	free(read);
	if (delete_quotes(&parse.lexer))
		return (ft_listclear(&parse.lexer), NULL);
	if (create_cmd_list(&parse))
		return (ft_listclear(&parse.lexer), ft_cmd_lstclear(&parse.cmd), NULL);
	ft_listclear(&parse.lexer);
	return (parse.cmd);
}
