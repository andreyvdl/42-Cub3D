#include "MLX42/include/MLX42/MLX42.h"
#include <stdio.h>
#include <stdlib.h>

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

int	main(int argc, char *argv[])
{
	t_mlx	mlx;

	if (argc != 2)
		return (puts("USA DIREITO"), 1);
	mlx.dist = (float)atof(argv[1]);
	if (mlx.dist < (float)0.1)
		return (puts("DISTANCIA INVALIDA"), 2);
	mlx.win = mlx_init(800, 600, "titulo", false);
	if (mlx.win == NULL)
		return (puts(mlx_strerror(mlx_errno)), 3);
	mlx.img = mlx_new_image(mlx.win, 800, 600);
	if (mlx.img == NULL)
		return (puts(mlx_strerror(mlx_errno)), mlx_terminate(mlx.win), 4);
	// dda_draw(mlx);
	// breseham_draw(mlx);
	// xiaolin_draw(mlx);
	mlx_image_to_window(mlx.win, mlx.img, 0, 0);
	mlx_loop(mlx.win);
	mlx_terminate(mlx.win);
	return (0);
}
