/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 20:54:12 by tozaki            #+#    #+#             */
/*   Updated: 2025/11/28 21:21:04 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include "libft/libft.h"


typedef struct s_server_state
{
	int		bit;
	int		client_pid;
	
}

volatile int	bit;
volatile int	c_pid;
char			c;
int				cnt;

void	sigusr1_handler(int signo, siginfo_t *info, void *content)
{
	c_pid = info->si_pid;
	ft_putnbr_fd(c_pid, 1);
	if (signo == SIGUSR1)
		bit = 1;
}

void	sigusr2_handler(int signo, siginfo_t *info, void *content)
{
	c_pid = info->si_pid;
	ft_putnbr_fd(c_pid, 1);
	if (signo == SIGUSR2)
		bit = 0;
}

void	recieve_char()
{
	c |= bit << cnt;
	cnt ++;
	if (cnt == 7)
	{
		ft_putchar_fd(c, 1);
		c = '\0';
		cnt = 0;
	}
	ft_putstr_fd("b\n", 1);
	kill(c_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	act1;
	struct sigaction	act2;
	int					pid;

	ft_bzero(&act1, sizeof(struct sigaction));
	act1.sa_sigaction = sigusr1_handler;
	sigemptyset(&act1.sa_mask);
	sigaction(SIGUSR1, &act1, NULL);
	ft_bzero(&act2, sizeof(struct sigaction));
	act2.sa_sigaction = sigusr2_handler;
	sigemptyset(&act2.sa_mask);
	sigaction(SIGUSR2, &act2, NULL);

	cnt = 0;
	c = '\0';
	pid = getpid();
	ft_putnbr_fd(pid, 1);
	ft_putchar_fd('\n', 1);
	pause();
	while (1)
	{
		ft_putstr_fd("a\n", 1);
		recieve_char();
		pause();
	}
	return (0);
}