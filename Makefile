# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlange <jlange@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/28 12:33:38 by jlange            #+#    #+#              #
#    Updated: 2019/03/05 02:09:50 by jlange           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


.PHONY: all, clean, fclean, re

SRC_PATH = src

OBJ_PATH = obj

NAME = wolf3d

CC = cc

HEADER = include/wolf3d.h

CFLAGS = -Wall -Wextra -Werror

CPPFLAGS = -Iinclude -Imlx_sierra

SRC_NAME =  main.c							\
						display_hook.c			\
						fill_tab.c					\
						tools.c							\
						tools2.c						\
						error.c 						\
						free.c 							\
						init_textures.c 		\
						init.c 							\
						intersection1.c 		\
						intersection2.c 		\
						minimap_draw.c	 		\
						minimap.c				 		\
						screen.c 						\
						math.c 							\
						floor_casting.c 		\
						moove.c 						\
						key_press_hook.c		\
						key_release_hook.c	\
						maze_generator.c		\
						init_maze.c					\
						place_player.c			\

OBJ = $(SRC_NAME:.c=.o)

OBJS = $(addprefix obj/, $(OBJ))

all: $(NAME)

$(NAME): obj/ $(OBJS)
	@$(CC) $(OBJS) libft/libft.a mlx_sierra/libmlx.a -framework OpenGl -framework AppKit -o $(NAME)

obj/:
	@make -C libft
	@make -C mlx_sierra
	@mkdir $(OBJ_PATH) 2> /dev/null

obj/%.o: src/%.c $(HEADER)
	@$(CC) -o $@ $(CPPFLAGS) -c $< $(CFLAGS)

clean:
	@make clean -C libft
	@make clean -C mlx_sierra
	@rm -rf $(OBJ_PATH)

fclean:
	@make fclean -C libft
	@make clean -C mlx_sierra
	@rm -rf $(NAME) $(OBJ_PATH) $(NAME)

re: fclean all
