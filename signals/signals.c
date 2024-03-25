/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:09:10 by ctruchot          #+#    #+#             */
/*   Updated: 2024/03/25 12:55:59 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int x = 0; // global variable

void handle_sigint(int sig)
{
	ft_printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}

int main(int ac, char**av)
{
	// kill(pid, SIGKILL);
	// wait(NULL);
	(void)ac;
	(void)av;
	// struct sigaction sa = { 0 }; // instantiate a struct and initialise to 0
	// struct sigaction sa; // instantiate a struct and initialise to 0
	// sa.sa_handler = &handle_sigint;// set up a function when 
	// sigaction(SIGINT, &sa, NULL); // 3rd parameter is the old sigaction, could be usefull to go back
	signal(SIGINT, handle_sigint);

	while (1)
	{
		printf("coucou\n");
		sleep(5);
	}

	// sa.sa_flags = SA_RESTART; // pas compris
	// alternative
	// signal(SIGTSTP, handle_sigtstp); // no need to use structure, does the same than above but manual page for signal function - 
	// for portability reasons use sigaction instead + to restore the signal handler better thanx to 3rd param
}


// signal(SIGTERM, handler);
// (void) signal(SIGINT, handler) ; // when SIGINT encountered, handler function is called, 
// (void) signal(SIGINT, SIG_IGN) ; // when SIGINT encountered, ignores the signal / but certain signals cannot be responded such as SIGKILL


// void handler(int num)
// {
// 	write(STDO, "I wont\n", 13)
// }