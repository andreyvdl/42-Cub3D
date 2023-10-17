#include "MLX42/include/MLX42/MLX42.h"
#include <stdio.h>

typedef struct s_mlx
{
	mlx_t		*window;
	mlx_image_t	*image;
}	t_mlx;

void	fun(void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	for (int i = 1; i <= 800; ++i)
		for (int j = 1; j <= 600; ++j)
			mlx_put_pixel(mlx->image, i - 1, j - 1, j ^ i);
	// experimente trocar o XOR por OR, AND e NOT
}

int	main(void)
{
	t_mlx	*mlx;

	mlx->window = mlx_init(800, 600, "titulo", true); // inicia a janela
	if (mlx->window == NULL)
		return (puts(mlx_strerror(mlx_errno)), 1);
	mlx->image = mlx_new_image(mlx->window, 800, 600); // cria uma imagem
	if (mlx->image == NULL)
		return (puts(mlx_strerror(mlx_errno)), mlx_terminate(mlx->window), 2);
	mlx_loop_hook(mlx->window, fun, mlx);
	mlx_image_to_window(mlx->window, mlx->image, 0, 0);
	mlx_loop(mlx->window); // fica em loop
	mlx_terminate(mlx->window); // da free na coisas q a mlx alocou
	return (0);
}
