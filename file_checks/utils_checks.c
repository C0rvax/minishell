/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:14:49 by ctruchot          #+#    #+#             */
/*   Updated: 2024/03/29 16:49:42 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_checks.h"

extern int status_code;

void	kill_child(t_cmd *cmd, int code)
{
	cmd->type = KILLED;
	cmd->code_err = code;
	status_code = code;
}

void	print_str_fd(char *s1, char *s2, char *s3, int fd)
{
	ft_putstr_fd(s1, fd);
	ft_putstr_fd(s2, fd);
	ft_putstr_fd(s3, fd);
}

int	ft_cmd_lstsize(t_cmd *lst)
{
	int	size;

	size = 0;
	if (!lst)
		return (size);
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}

t_redirect	*ft_in_lstlast(t_redirect *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_in_lstclear(t_redirect *lst)
{
	t_redirect	*buff;

	if (!lst)
		return ;
	while (lst->next)
	{
		buff = lst->next;
		free(lst->path);
		free(lst);
		lst = buff;
	}
}
