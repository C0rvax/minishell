/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:09:10 by ctruchot          #+#    #+#             */
/*   Updated: 2024/04/08 16:21:46 by aduvilla         ###   ########.fr       */
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

void	handle_heredoc(int sig)
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
	struct sigaction	hdint;
	struct sigaction	hdquit;

	sigemptyset(&hdint.sa_mask);
	hdint.sa_handler = &handle_heredoc;
	hdint.sa_flags = 0;
	sigemptyset(&hdquit.sa_mask);
	hdquit.sa_handler = SIG_IGN;
	hdquit.sa_flags = 0;
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
	if (sig == 3)
	{
		sigaction(SIGINT, &hdint, NULL);
		sigaction(SIGQUIT, &hdquit, NULL);
	}
}
