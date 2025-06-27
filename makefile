# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: manelcarvalho <manelcarvalho@student.42    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/16 23:27:33 by mcarvalh          #+#    #+#              #
#    Updated: 2025/06/27 02:00:19 by manelcarval      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CFLAGS = -Wall -Wextra -Werror -pthread -g -fsanitize=address
SRC_DIR = src/
OBJ_DIR = obj/

SRC = main.c data_init.c exits.c utils.c dead_or_alive.c threads_utils.c print.c simulation.c routines.c

SRCS = $(addprefix $(SRC_DIR), $(SRC))
OBJS = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

INC = -I ./inc/

all: $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	cc $(CFLAGS) -c $< -o $@ $(INC)

$(NAME): $(OBJS)
	cc $(CFLAGS) $(OBJS) -o $(NAME)
	

# VALGRIND = valgrind
# VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --track-fds=yes --suppressions=readline.supp

# valgrind: $(NAME)
# 	$(VALGRIND) $(VALGRIND_FLAGS) ./$(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re valgrind