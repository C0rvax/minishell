/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:16:25 by ctruchot          #+#    #+#             */
/*   Updated: 2024/04/16 17:38:01 by ctruchot         ###   ########.fr       */
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

void	get_status(int status
		// if (check_infiles(cmd, total_cmd, pers) != 0)
		// // return 1 si pb, ou si 1 seule commande killed
		// // fin du check et pas dexec
		// if (check_outfiles(cmd, total_cmd, pers) != 0)  // return 1 si pareil
		// // fin du check et pas dexec
		// if (check_cmd(cmd, total_cmd, mini_env, pers) != 0)
		// //  returns 1 only if is a directory and only child + issue
		// // or no path is found and only one child
		// if (check_infiles(cmd, total_cmd, pers) != 0)
		// // return 1 si pb, ou si 1 seule commande killed
		// // fin du check et pas dexec
		// if (check_outfiles(cmd, total_cmd, pers) != 0)  // return 1 si pareil
		// // fin du check et pas dexec
		// if (check_cmd(cmd, total_cmd, mini_env, pers) != 0)
		// //  returns 1 only if is a directory and only child + issue
		// // or no path is found and only one child, t_pers *pers)
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
	}
}
