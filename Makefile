
NAME		=	cub3D

SCRS		=	get_next_line.c main.c utils.c
OBJS_FOLDER_DIR_PATH =	objs/
OBJS		=	$(addprefix $(OBJS_FOLDER_DIR_PATH),$(SCRS:%.c=%.o))

FLAGS		=	

RM			=	rm -f

all: dir $(NAME)

$(OBJS_FOLDER_DIR_PATH)%.o: %.c
	cc $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	cc $(FLAGS) $^ -o $@

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