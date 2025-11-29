
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 20:54:07 by tozaki            #+#    #+#             */
/*   Updated: 2025/11/28 19:42:51 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include "client.h"
#include "libft/libft.h"
#include <stdlib.h>

t_client_status		c_stat;

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
	int	timeout;

	i = 0;
	while (i < 8)
	{
		c_stat.ack_received = 0;
		send_bit(s_pid, (c >> i) & 1);
		
		// ACKを待つ（タイムアウト付き）
		timeout = 0;
		while (!c_stat.ack_received && timeout < 1000)
		{
			usleep(100);  // 100マイクロ秒待機
			timeout++;
		}
		
		if (!c_stat.ack_received)
		{
			ft_putstr_fd("Timeout waiting for ACK\n", 2);
			return;
		}
		
		i++;
	}
}

void	send_string(int s_pid, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putchar_fd('.', 1);  // 進捗表示
		send_char(s_pid, str[i]);
		i++;
	}
	ft_putchar_fd('.', 1);
	send_char(s_pid, '\0');
	ft_putstr_fd("\nDone!\n", 1);
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
	{
		ft_putstr_fd("Usage: ./client [server_pid] [message]\n", 2);
		return (1);
	}
	ft_bzero(&act, sizeof(struct sigaction));
	act.sa_handler = ack_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_RESTART;  // システムコールの自動再開
	sigaction(SIGUSR1, &act, NULL);
	init_status();
	send_string(ft_atoi(argv[1]), argv[2]);
	return (0);
}