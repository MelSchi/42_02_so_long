# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mschiman <mschiman@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/14 11:48:46 by mschiman          #+#    #+#              #
#    Updated: 2022/03/27 12:11:58 by mschiman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	./src/main.c \
		./src/ft_strjoins.c \
		./src/read_map.c \
		./src/error_exit.c \
		./src/image.c \
		./src/move_pl.c \
		./src/move_nm.c \
		./src/gnl_so_long.c

NAME = so_long
CC = gcc
CFLAGS = -Wall -Wextra -Werror
MLX_MAC = ./mlx_mac
LIBFT = libft
INCLMLX =-L$(MLX_MAC) -lmlx -framework OpenGL -framework Appkit
OBJS = ${SRC:.c=.o}

$(NAME) : $(OBJS)
		@make  -C ./libft
		@make  bonus -C ./libft
		@make all -C mlx_mac
		$(CC) $(CFLAGS) $(SRC) $(INCLMLX) -L$(LIBFT) -lft -o $(NAME)
		
all:	$(NAME)

clean:
		@make clean -C ./libft
		@make clean -C ./mlx_mac
		@rm -f ${OBJS}

fclean: clean
	-rm $(NAME)
	@make fclean -C ./libft

re: fclean all

.PHONY: clean fclean re re_bonus all