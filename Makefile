# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abel-mak <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/06 20:14:20 by abel-mak          #+#    #+#              #
#    Updated: 2020/11/18 08:36:18 by abel-mak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INCLUDE= /usr/local/include/ 

LAMLX = /usr/local/lib/

LIBFT = ./libft/libft.a

HEADER_B= cube_bonus.h

HEADER= cube.h

NAME = cub3D

BONUS= cub3D_bonus

SRC = src/mlx.c src/parse.c src/save.c src/init.c src/init_cont.c src/gun.c \
	  src/game.c src/draw.c src/draw_cont.c src/map.c src/player.c src/draw_utils.c \
	  src/angle_utils.c src/utils.c src/sprite.c src/lst.c src/parse_map.c \
	  src/parse_r_color.c src/parse_error.c src/parse_utils.c


FLAGS = -Wall -Werror -Wextra

SRC_BONUS = src_bonus/mlx_bonus.c src_bonus/parse_bonus.c\
			src_bonus/save_bonus.c src_bonus/init_bonus.c \
			src_bonus/gun_bonus.c src_bonus/game_bonus.c \
			src_bonus/draw_bonus.c src_bonus/draw_cont_bonus.c\
			src_bonus/map_bonus.c src_bonus/player_bonus.c \
			src_bonus/draw_utils_bonus.c src_bonus/angle_utils_bonus.c \
			src_bonus/utils_bonus.c src_bonus/sprite_bonus.c\
			src_bonus/lst_bonus.c src_bonus/parse_map_bonus.c\
			src_bonus/parse_r_color_bonus.c src_bonus/parse_error_bonus.c \
			src_bonus/parse_utils_bonus.c src_bonus/init_cont_bonus.c

OBJ= $(SRC:.c=.o)

OBJ_BONUS= $(SRC_BONUS:.c=.o)

all:$(NAME)

bonus: $(BONUS)

$(BONUS): $(LIBFT) $(OBJ_BONUS) $(HEADER_B)
	gcc $(FLAGS) $(OBJ_BONUS) -I $(INCLUDE) -I . -I ./libft -L $(LAMLX) \
	-lmlx -framework OpenGL -framework AppKit -L ./libft -lft -o $(BONUS)

$(NAME): $(LIBFT) $(OBJ) $(HEADER)
	gcc $(FLAGS) $(OBJ) -I $(INCLUDE) -I . -I ./libft -L $(LAMLX) \
	-lmlx -framework OpenGL -framework AppKit -L ./libft -lft -o $(NAME)

%.o:%.c
	gcc -c $(FLAGS) $< -o $@

$(LIBFT):
	make -C ./libft/

clean:
	make clean -C ./libft
	rm -rf $(OBJ)
	rm -rf $(OBJ_BONUS)
fclean:clean
	rm -rf $(NAME)
	rm -rf $(BONUS)
	make fclean -C ./libft

re:	fclean
	make 
