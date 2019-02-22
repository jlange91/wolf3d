# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlange <jlange@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/28 12:33:38 by jlange            #+#    #+#              #
#    Updated: 2018/04/10 19:01:40 by jlange           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


.PHONY: all, clean, fclean, re

SRC_PATH = src

OBJ_PATH = obj

NAME = wolf3d

CC = cc

HEADER = include/wolf3d.h

CFLAGS = -Wall -Wextra -Werror

CPPFLAGS = -Iinclude -ImlxSierra

SRC_NAME =  main.c							\
						display_hook.c			\
						fill_tab.c					\
						tools.c							\
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

OBJ = $(SRC_NAME:.c=.o)

OBJS = $(addprefix obj/, $(OBJ))

all: $(NAME)

$(NAME): obj/ $(OBJS)
	@$(CC) -g $(OBJS) libft/libft.a mlxCapitan/libmlx.a -framework OpenGl -framework AppKit -o $(NAME) -fsanitize=address 

obj/:
	@make -C libft
	@mkdir $(OBJ_PATH) 2> /dev/null

obj/%.o: src/%.c $(HEADER)
	@$(CC) -o $@ $(CPPFLAGS) -c $< $(CFLAGS)

clean:
	@make clean -C libft
	@rm -rf $(OBJ_PATH)

fclean:
	@make fclean -C libft
	@rm -rf $(NAME) $(OBJ_PATH) $(NAME)

re: fclean all
