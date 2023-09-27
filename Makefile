
NAME					=	cub3D

SCRS					=	ft_split.c get_next_line.c main.c utils.c
OBJS_FOLDER_DIR_PATH	=	objs/
OBJS					=	$(addprefix $(OBJS_FOLDER_DIR_PATH),$(SCRS:%.c=%.o))

FLAGS					=	-g

RM						=	rm -f

all: dir $(NAME)

$(OBJS_FOLDER_DIR_PATH)%.o: %.c cube.h
	cc $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	cc $(FLAGS) $^ MLX42/build/libmlx42.a -o $@ -g3 -ldl -lglfw -pthread -lm

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
	./$(NAME) f.cub

v: all
	clear && valgrind --suppressions=log1 --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=log ./$(NAME) f.cub
	
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