/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 16:33:43 by tozaki            #+#    #+#             */
/*   Updated: 2025/11/29 15:44:19 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <signal.h>

typedef struct s_client_status
{
	int		ack_received;
	int		char_cnt;
	int		bit_cnt;
	int		s_pid;
	char	*str;
}		t_client_status;
#endif