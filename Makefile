# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adantas-, rleite-s <adantas-@student.42    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/20 20:23:03 by adantas-, r       #+#    #+#              #
#    Updated: 2023/10/25 12:28:06 by adantas-, r      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	cub3D

SCRS				=	$(addprefix srcs/, attributes_functions.c cast_rays.c \
							draw_wall.c element_functions.c error_message.c ft_atoi.c \
							ft_split.c get_next_line.c get_next_line_utils.c map_change_walls.c\
							has_invalid_functions.c keyboard.c main.c map_functions.c \
							player_globals.c render.c visual_start.c world_globals.c) \
							$(addprefix utils/, map_utils.c math_utils.c matrix_utils.c \
							mem_utils.c str_utils.c str_utils2.c)
OBJS				=	$(SCRS:%.c=%.o)

SCRS_BONUS			=	$(addprefix srcs/, attributes_functions.c cast_rays.c \
							draw_wall.c element_functions.c error_message.c ft_atoi.c \
							ft_split.c get_next_line.c get_next_line_utils.c map_change_walls.c\
							has_invalid_functions.c main.c map_functions.c \
							player_globals.c world_globals.c) \
							$(addprefix utils/, map_utils.c matrix_utils.c \
							mem_utils.c str_utils.c str_utils2.c) \
							$(addprefix bonus/, keyboard_bonus.c math_utils_bonus.c \
							mouse_bonus.c render_bonus.c visual_start_bonus.c)
OBJS_BONUS			=	$(SCRS_BONUS:%.c=%.o)

FLAGS				=	-Wall -Wextra -Werror -g
MLX_FLAGS			=	-lm -ldl -pthread -lglfw
INCLUDE				=	-I includes

RM					=	rm -f

BONUS_EXISTS		=	$(wildcard $(addprefix bonus/, keyboard_bonus.o render_bonus.o visual_start_bonus.o))
MANDATORY_EXISTS	=	$(wildcard $(addprefix srcs/, keyboard.o render.o visual_start.o))

all: MLX42/build/libmlx42.a $(NAME)

MLX42/build/libmlx42.a:
ifeq (, $(wildcard MLX42/build))
	cmake -S MLX42 -B MLX42/build
	cmake -S MLX42 --build MLX42/build
endif
	@make -j4 -C MLX42/build

%.o: %.c includes/cube.h includes/defines.h
	cc $(FLAGS) -c $< -o $@ $(INCLUDE)

$(NAME): $(if $(BONUS_EXISTS), $(OBJS_BONUS), $(OBJS))
	cc $(FLAGS) $^ MLX42/build/libmlx42.a -o $@ $(MLX_FLAGS) $(INCLUDE)

clean:
ifeq (MLX42/build/Makefile, $(wildcard MLX42/build/Makefile))
	@make -C MLX42/build clean
endif
	$(RM) -r MLX42/build
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
	$(RM) -r MLX42/build
	$(RM) $(NAME)

re: fclean
	@make --no-print-directory
	
re_bonus: fclean bonus

bonus: $(if $(MANDATORY_EXISTS), fclean)
	@make OBJS="$(OBJS_BONUS)" --no-print-directory

.PHONY: all clean fclean re bonus

v: all
	clear && valgrind --leak-check=full --show-leak-kinds=all --suppressions=codam.sup --log-file=log ./$(NAME) maps/$(MAP).cub
	
norm:
	@norminette $(SCRS) $(SCRS_BONUS) $(wildcard $(addprefix includes/, defines.h cube.h))
