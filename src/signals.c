/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:09:10 by ctruchot          #+#    #+#             */
/*   Updated: 2024/03/30 15:39:37 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	g_status = 130;
	ft_printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}

void	handle_sigint_inprocess(int sig)
{
	g_status = 130;
	ft_printf("\n");
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

void	signals(int sig)
{
	if (sig == 1)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == 2)
	{
		signal(SIGINT, handle_sigint_inprocess);
		signal(SIGQUIT, handle_sigquit);
	}
}
