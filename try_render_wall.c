#include "MLX42/include/MLX42/MLX42.h"
#include <stdio.h>
#include <stdlib.h>
// gcc try_render_wall.c MLX42/build/libmlx42.a -g3 -ldl -lglfw -pthread -lm

typedef struct s_mlx
{
	mlx_t		*win;
	mlx_image_t	*img;
	float		dist;
}	t_mlx;

//https://www.youtube.com/watch?v=0auShy9_Qzo
// codigo do video
// https://github.com/jarreed0/random_projects/blob/main/lines/line.cpp
// dos 3 o DDA parece o mais facil de implementar seguido pelo Xiaolin

// https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm)
void	dda_draw(t_mlx *mlx)
{
}

// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
void	breseham_draw(t_mlx *mlx)
{
}

// https://en.wikipedia.org/wiki/Xiaolin_Wu's_line_algorithm
// teoricamente faz anti-aliasing
void	xiaolin_draw(t_mlx *mlx)
{
}

void	throw_rays(t_mlx *mlx, int width)
{
}

void	render_wall(t_mlx *mlx)
{
	int	width;
	int	wall_h;
	int	dist;

	width = 0;
	while (width < 800)
	{
		dist = mlx->dist;
		wall_h = mlx->dist;
		while (dist++ < 600 - mlx->dist)
		{
			mlx_put_pixel(mlx->img, width, wall_h, 0x00FF00FF);
			wall_h++;
		}
		width++;
	}
}

int	main(int argc, char *argv[])
{
	t_mlx	mlx;

	if (argc != 2)
		return (puts("USA DIREITO"), 1);
	mlx.dist = atoi(argv[1]);
	if (mlx.dist < 1)
		return (puts("DISTANCIA INVALIDA"), 2);
	mlx.win = mlx_init(800, 600, "titulo", false);
	if (mlx.win == NULL)
		return (puts(mlx_strerror(mlx_errno)), 3);
	mlx.img = mlx_new_image(mlx.win, 800, 600);
	if (mlx.img == NULL)
		return (puts(mlx_strerror(mlx_errno)), mlx_terminate(mlx.win), 4);
	render_wall(&mlx);
	// throw_rays(&mlx, 801);
	// dda_draw(mlx);
	// breseham_draw(mlx);
	// xiaolin_draw(mlx);
	mlx_image_to_window(mlx.win, mlx.img, 0, 0);
	mlx_loop(mlx.win);
	mlx_terminate(mlx.win);
	return (0);
}
