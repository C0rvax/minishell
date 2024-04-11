/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Prompted_gnl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:32:43 by aduvilla          #+#    #+#             */
/*   Updated: 2024/04/11 17:30:06 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "minishell.h" 

char	*prompted_gnl(char *prompt, int fd, int mode)
{
	char	*gnl;
	char	*cpy;

	ft_putstr(prompt);
	cpy = get_next_line(fd);
	if (!cpy)
		return (NULL);
	if (mode == 1)
		return (cpy);
	else
	{
		gnl = ft_substr(cpy, 0, ft_strlen(cpy) - 1);
		free(cpy);
		return (gnl);
	}
}
