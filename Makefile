# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adantas- <adantas-@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/16 11:01:50 by adantas-, r       #+#    #+#              #
#    Updated: 2023/10/17 13:32:40 by adantas-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME					=	cub3D

SCRS					=	arg_validate.c attributes_functions.c cub_enviesado.c cast_rays.c element_functions.c error_message.c files.c ft_split.c get_next_line.c has_invalid_functions.c keyboard.c map_functions.c map_utils.c mouse.c render.c utils.c utils1.c fake_globals.c
OBJS_FOLDER_DIR_PATH	=	objs/
OBJS					=	$(addprefix $(OBJS_FOLDER_DIR_PATH),$(SCRS:%.c=%.o))

FLAGS					=	-g

RM						=	rm -f

all: dir $(NAME)

$(OBJS_FOLDER_DIR_PATH)%.o: %.c
	cc $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
#												-g -lm -ldl -pthread -lglfw 
#	cc $(FLAGS) $^ MLX42/build/libmlx42.a -o $@ -g -ldl -lglfw -pthread -lm
	cc $(FLAGS) $^ MLX42/build/libmlx42.a -o $@ -g -lm -ldl -pthread -lglfw 

dir:
	$(if ifeq ($(wildcard $(OBJS_FOLDER_DIR_PATH)),), \
		$(shell mkdir -p $(OBJS_FOLDER_DIR_PATH)))

clean:
	$(RM) $(OBJS) -r $(OBJS_FOLDER_DIR_PATH)

fclean: clean
	$(RM) $(NAME)

re: fclean all
#	make

.PHONY: all clean fclean re

r: all
	./$(NAME) #f.cub

v: all
	clear && valgrind --suppressions=log1 --log-file=log ./$(NAME) #f.cub
	
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
