/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 20:54:07 by tozaki            #+#    #+#             */
/*   Updated: 2025/11/29 13:34:55 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include "client.h"
#include "libft/libft.h"
#include <stdlib.h>

volatile t_client_status		c_stat;

void	ack_handler(int signo)
{
	(void)signo;
	c_stat.ack_received = 1;
}

void	send_bit(int s_pid, int bit)
{
	if (bit)
		kill(s_pid, SIGUSR1);
	else
		kill(s_pid, SIGUSR2);
}

void	send_char(int s_pid, char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		c_stat.ack_received = 0;
		send_bit(s_pid, (c >> i) & 1);
		while (!c_stat.ack_received)
			pause();
		i++;
	}
}

void	send_string(int s_pid, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		send_char(s_pid, str[i]);
		i++;
	}
	send_char(s_pid, '\0');
}

void	init_status(void)
{
	c_stat.ack_received = 0;
	c_stat.char_cnt = 0;
	c_stat.bit_cnt = 0;
}

int	main(int argc, char **argv)
{
	struct sigaction	act;

	if (argc != 3)
		return (1);
	ft_bzero(&act, sizeof(struct sigaction));
	act.sa_handler = ack_handler;
	sigemptyset(&act.sa_mask);
	sigaction(SIGUSR1, &act, NULL);
	init_status();
	send_string(ft_atoi(argv[1]), argv[2]);
	return (0);
}

/**
 * struct sigaction {
 * 		void     (*sa_handler)(int);
 * 		void     (*sa_sigaction)(int, siginfo_t *, void *);
 * 		sigset_t   sa_mask;
 * 		int        sa_flags;
 * 		void     (*sa_restorer)(void);
 * };
 */
