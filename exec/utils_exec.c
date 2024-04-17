/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:16:25 by ctruchot          #+#    #+#             */
/*   Updated: 2024/04/17 15:50:03 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	free_tab_int(int **fd, int nb)
{
	int	i;

	i = 0;
	while (i < nb && fd[i] != NULL)
	{
		free(fd[i]);
		i++;
	}
	free(fd);
	fd = NULL;
	return (0);
}

void	get_status(int status, t_pers *pers)
{
	if (WIFEXITED(status))
		pers->status_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (status == 139)
		{
			ft_putstr_fd("Segmentation fault (core dumped)\n", 2);
			pers->status_code = status;
		}
		else if (status == 131)
			pers->status_code = status;
		else
			pers->status_code = status + 128;
		g_status = 0;
	}
}
