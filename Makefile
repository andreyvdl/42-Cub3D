
temp:
	cc cub_enviesado.c cast_rays.c keyboard.c mouse.c render.c utils.c MLX42/build/libmlx42.a -Wall -Wextra -Werror -g -lm -ldl -pthread -lglfw && ./a.out
