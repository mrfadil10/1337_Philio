# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/17 10:59:16 by mfadil            #+#    #+#              #
#    Updated: 2023/06/17 14:04:59 by mfadil           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= cc
CFLAGS	= -Wall -Wextra -Werror
NAME	= philo
O_PATH	= obj/

LIBFT_LIB = Libft/libft.a

SRC		=		life_cycle.c \
				tools.c \
				start.c \
				main.c

OBJ		= $(SRC:.c=.o)
OBJS	= $(addprefix $(O_PATH), $(OBJ))

all: $(NAME)

$(O_PATH)%.o: %.c philos.h ./Libft/libft.h
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT_LIB)
	$(CC) $(OBJS) Libft/libft.a -o $(NAME)

clean:
	rm -rf ./obj/*.o
	make -C Libft clean

$(LIBFT_LIB) :
	make -C Libft

fclean: clean
	rm -f $(NAME)
	rm -f ./Libft/libft.a

re: fclean all
