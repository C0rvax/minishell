/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 14:13:14 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/11 18:05:11 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cmd_lstclear(t_cmd **cmd)
{
	t_cmd	*buf;

	if (!*cmd)
		return ;
	while ((*cmd)->next)
	{
		buf = (*cmd)->next;
		ft_freetab((*cmd)->argv);
		ft_redir_listclear(&(*cmd)->in);
		ft_redir_listclear(&(*cmd)->out);
		free(*cmd);
		*cmd = buf;
	}
	ft_freetab((*cmd)->argv);
	ft_redir_listclear(&((*cmd)->in));
	ft_redir_listclear(&(*cmd)->out);
	free(*cmd);
	*cmd = NULL;
}

t_cmd	*ft_cmd_lstnew(char **argv)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd) * 1);
	if (!new)
		return (NULL);
	new->argv = argv;
	if (!new->argv)
		return (free(new), NULL);
	new->in = NULL;
	new->out = NULL;
	new->next = NULL;
	return (new);
}

t_cmd	*ft_cmd_lstlast(t_cmd *list)
{
	if (!list)
		return (NULL);
	while (list->next != NULL)
		list = list->next;
	return (list);
}

void	ft_cmd_lstadd_back(t_cmd **list, t_cmd *new)
{
	t_cmd	*buf;

	if (!list || !new)
		return ;
	if (*list == NULL)
		*list = new;
	else
	{
		buf = ft_cmd_lstlast(*(list));
		buf->next = new;
	}
}

void	print_cmd_lst(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd)
	{
		while (cmd)
		{
			ft_putar(cmd->argv);
			print_redir_lst(cmd->in);
			print_redir_lst(cmd->out);
			cmd = cmd->next;
			i++;
		}
	}
}
