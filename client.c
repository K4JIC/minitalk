/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 20:54:07 by tozaki            #+#    #+#             */
/*   Updated: 2025/11/29 15:47:33 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include "client.h"
#include "libft/libft.h"
#include <stdlib.h>

volatile t_client_status	g_client;

void	send_bit(int signo)
{
	int	bit;

	if (signo != SIGUSR1)
		return ;
	if (g_client.bit_cnt == 8)
	{
		g_client.bit_cnt = 0;
		if (!g_client.str[g_client.char_cnt])
		{
			g_client.char_cnt++;
			return ;
		}
		g_client.char_cnt++;
	}
	bit = (g_client.str[g_client.char_cnt] >> g_client.bit_cnt) & 1;
	g_client.bit_cnt++;
	if (bit)
		kill(g_client.s_pid, SIGUSR1);
	else
		kill(g_client.s_pid, SIGUSR2);
}

void	error_msg(void)
{
	ft_putstr_fd("Invalid PID\n", 2);
}

int	main(int argc, char **argv)
{
	struct sigaction	act;
	size_t				slen;

	if (argc != 3)
		return (1);
	ft_bzero(&act, sizeof(struct sigaction));
	act.sa_handler = send_bit;
	sigemptyset(&act.sa_mask);
	sigaction(SIGUSR1, &act, NULL);
	g_client.ack_received = 0;
	g_client.char_cnt = 0;
	g_client.bit_cnt = 0;
	g_client.str = argv[2];
	g_client.s_pid = ft_atoi(argv[1]);
	if (g_client.s_pid <= 0)
		return (error_msg(), 1);
	slen = ft_strlen(argv[2]);
	send_bit(SIGUSR1);
	while (g_client.char_cnt <= (int)slen)
		pause();
	return (0);
}
