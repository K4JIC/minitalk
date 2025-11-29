/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 20:54:12 by tozaki            #+#    #+#             */
/*   Updated: 2025/11/29 13:32:45 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include "libft/libft.h"
#include "server.h"

volatile t_server	g_server;

void	signal_handler(int signo, siginfo_t *info, void *context)
{
	(void)context;

	if (signo == SIGUSR1)
		g_server.bit = 1;
	else if (signo == SIGUSR2)
		g_server.bit = 0;
	g_server.c |= (g_server.bit << g_server.cnt);
	g_server.cnt++;
	if (g_server.cnt == 8)
	{
		if (g_server.c == '\0')
			ft_putchar_fd('\n', 1);
		else
			ft_putchar_fd(g_server.c, 1);
		g_server.c = 0;
		g_server.cnt = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	act;
	int					pid;

	ft_bzero(&act, sizeof(struct sigaction));
	act.sa_sigaction = signal_handler;
	act.sa_flags = SA_SIGINFO;
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGUSR1); 
	sigaddset(&act.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	g_server.cnt = 0;
	g_server.c = 0;
	g_server.bit = 0;
	pid = getpid();
	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(pid, 1);
	ft_putchar_fd('\n', 1);
	while (1)
		pause();
	return (0);
}