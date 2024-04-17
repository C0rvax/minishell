/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:34:40 by ctruchot          #+#    #+#             */
/*   Updated: 2024/04/17 15:37:35 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handle_sigquit_several(int sig)
{
	g_status = 0;
	rl_replace_line("", 0);
	rl_on_new_line();
	(void)sig;
}

void	handle_sigquit(int sig)
{
	g_status = 131;
	ft_printf("Quit (core dumped)\n");
	(void)sig;
}
