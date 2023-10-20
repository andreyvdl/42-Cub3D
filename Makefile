# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adantas-, rleite-s <adantas-@student.42    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/20 20:23:03 by adantas-, r       #+#    #+#              #
#    Updated: 2023/10/20 20:23:08 by adantas-, r      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME					=	cub3D

SCRS					=	$(addprefix srcs/, attributes_functions.c cast_rays.c \
							draw_wall.c element_functions.c error_message.c ft_atoi.c \
							ft_split.c get_next_line.c get_next_line_utils.c \
							has_invalid_functions.c keyboard.c main.c map_functions.c \
							mouse.c player_globals.c render.c visual_start.c world_globals.c) \
							$(addprefix utils/, map_utils.c math_utils.c matrix_utils.c \
							mem_utils.c str_utils.c str_utils2.c)
#OBJS_FOLDER_DIR_PATH	=	objs/
OBJS					=	$(SCRS:%.c=%.o)

FLAGS					=	-Wall -Wextra -Werror -g
MLX_FLAGS				=	-lm -ldl -pthread -lglfw
INCLUDE					=	-I includes

RM						=	rm -f

all: $(NAME)

%.o: %.c
	cc $(FLAGS) -c $< -o $@ $(INCLUDE)

$(NAME): $(OBJS)
	cc $(FLAGS) $^ MLX42/build/libmlx42.a -o $@ $(MLX_FLAGS) $(INCLUDE)

dir:
	$(if ifeq ($(wildcard $(OBJS_FOLDER_DIR_PATH)),), \
		$(shell mkdir -p $(OBJS_FOLDER_DIR_PATH)))

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
#	make

.PHONY: all clean fclean re

r: all
	./$(NAME) maps/valid.cub

v: all
	clear && valgrind --leak-check=summary --suppressions=codam.sup --log-file=log ./$(NAME) maps/valid.cub
	
#############################
# 			MLX CODAM		#
#############################
#
# Remover as pastas: .git e .github
#
# Tem que mudar a versão do cmake pra uma que a máquina aguente (cmake --version)
# cmake -B <nome de pasta>
# cmake --build <nome da pasta criada anteriormente>
# (libmlx42.a) estará criada na pasta que você atribuiu o nome


temp:
	cc cub_enviesado.c cast_rays.c keyboard.c mouse.c render.c utils.c MLX42/build/libmlx42.a -Wall -Wextra -Werror -g -lm -ldl -pthread -lglfw && valgrind ./a.out

norm:
	norminette $(SCRS)

w:
	watch -n0 norminette $(SCRS)
