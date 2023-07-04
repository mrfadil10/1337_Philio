# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/17 10:59:16 by mfadil            #+#    #+#              #
#    Updated: 2023/07/04 22:49:50 by mfadil           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= cc
CFLAGS	= -Wall -Wextra -Werror
NAME	= philo
O_PATH	= obj/

SRC		=		life_cycle.c \
				dead_philo.c \
				philo_tools.c \
				start.c \
				utils.c \
				main.c

OBJ		= $(SRC:.c=.o)
OBJS	= $(addprefix $(O_PATH), $(OBJ))

GLOBAL_DEP = Makefile \
			 philos.h \

all: $(NAME)

$(O_PATH)%.o: %.c $(GLOBAL_DEP)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(GLOBAL_DEP)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf ./obj/*.o

fclean: clean
	rm -f $(NAME)

re: fclean all