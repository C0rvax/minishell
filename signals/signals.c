/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:09:10 by ctruchot          #+#    #+#             */
/*   Updated: 2024/03/08 15:09:25 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>

int x = 0; // global variable

void handle_sigtstp(int sig)
{
	printf("non-stop");
}

int main(int ac, char**av)
{
	struct sigaction sa = { 0 }; // instantiate a struct and initialise to 0
	sa.sa_flags = SA_RESTART; // pas compris
	sa.sa_handler = &handle_sigtstp;// set up a function when 
	sigaction(SIGTSTP, &sa, NULL) // 3rd parameter is the old sigaction, could be usefull to go back

	// alternative
	signal(SIGTSTP, handle_sigtstp); // no need to use structure, does the same than above but manual page for signal function - 
	// for portability reasons use sigaction instead + to restore the signal handler better thanx to 3rd param
}


signal(SIGTERM, handler);
(void) signal(SIGINT, handler) ; // when SIGINT encountered, handler function is called, 
(void) signal(SIGINT, SIG_IGN) ; // when SIGINT encountered, ignores the signal / but certain signals cannot be responded such as SIGKILL


void handler(int num)
{
	write(STDO, "I wont\n", 13)
}