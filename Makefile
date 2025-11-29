# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tozaki <tozaki@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/29 13:00:34 by tozaki            #+#    #+#              #
#    Updated: 2025/11/29 13:31:52 by tozaki           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER	=	server
CLIENT	=	client
CC		=	cc
FALGS	=	-Wall -Wextra -Werror
S_SRCS	=	server.c
C_SRCS	=	client.c
S_OBJS	=	server.o
C_OBJS	=	client.o
S_HDRS	=	server.h
C_HDRS	=	client.h


.PHONY: all
all: $(SERVER) $(CLIENT)

$(SERVER): $(S_OBJS) libft/libft.a
	$(CC) $(S_OBJS) -o $(SERVER) libft/libft.a

$(CLIENT): $(C_OBJS) libft/libft.a
	$(CC) $(C_OBJS) -o $(CLIENT) libft/libft.a

$(S_OBJS): $(S_SRCS) $(S_HDRS)
	$(CC) $(FALGS) $(S_SRCS) -c

$(C_OBJS): $(C_SRCS) $(C_HDRS)
	$(CC) $(FALGS) $(C_SRCS) -c

libft/libft.a:
	make -C libft all

.PHONY: clean
clean:
	make -C libft clean
	rm -f $(S_OBJS)
	rm -f $(C_OBJS)

.PHONY: fclean
fclean: clean
	rm -f libft/libft.a
	rm -f server
	rm -f client

.PHONY: re
re: fclean all