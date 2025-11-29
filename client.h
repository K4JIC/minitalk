/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 16:33:43 by tozaki            #+#    #+#             */
/*   Updated: 2025/11/29 13:34:47 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIANT_H
# define CLIANT_H

#include <signal.h>

typedef struct s_client_status
{
	int	ack_received;
	int	pid_char_cnt;
	int	pid_bit_cnt;
	int	char_cnt;
	int	bit_cnt;
}		t_client_status;

#endif