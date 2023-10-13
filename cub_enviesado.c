#include "mlx_test.h"

double		g_player_x = SIZE * 1.5;
double		g_player_y = SIZE * 1.5;
int	 		g_player_angle;
double		g_dir_x;
double		g_dir_y;
const char	*g_map[]= {
	"1111111111111111",
	"1000000000000001",
	"1000000000000001",
	"1001100000011001",
	"1001100000011001",
	"1000000000000001",
	"1000000000000001",
	"1000000000000001",
	"1000000000000001",
	"1001100000011001",
	"1001100000011001",
	"1000000000000001",
	"1000000000000001",
	"1111111111111111",
	NULL
};

double	deg_to_rad(int deg)
{
	return (deg * RAD_1);
}

/* void	draw_ray(t_mlx *mlx, double x0, double y0, double x1, double y1, uint32_t color)
{
	double	dist_x;
	double	dist_y;
	double	step;

	dist_x = x1 - x0;
	dist_y = y1 - y0;
	if (fabs(dist_x) > fabs(dist_y))
		step = fabs(dist_x);
	else
		step = fabs(dist_y);
	dist_x /= step;
	dist_y /= step;
	while ((int)step--)
	{
		if (x0 <= 0 || y0 <= 0 || x0 >= 499 || y0 >= 399)
			break ;
		mlx_put_pixel(mlx->img, x0, y0, color);
		x0 += dist_x;
		y0 += dist_y;
	}
} */

bool	load_textures(t_mlx *mlx)
{
	mlx->tex[NO] = mlx_load_png("NORTH2.png");
	if (mlx->tex[NO] == NULL)
		return (puts(mlx_strerror(mlx_errno)), true);
	mlx->tex[SO] = mlx_load_png("SOUTH2.png");
	if (mlx->tex[SO] == NULL)
		return (puts(mlx_strerror(mlx_errno)), mlx_delete_texture(mlx->tex[NO]), true);
	mlx->tex[WE] = mlx_load_png("WEST2.png");
	if (mlx->tex[WE] == NULL)
		return (puts(mlx_strerror(mlx_errno)), mlx_delete_texture(mlx->tex[NO]), mlx_delete_texture(mlx->tex[SO]), true);
	mlx->tex[EA] = mlx_load_png("EAST2.png");
	if (mlx->tex[EA] == NULL)
		return (puts(mlx_strerror(mlx_errno)), mlx_delete_texture(mlx->tex[NO]), mlx_delete_texture(mlx->tex[SO]), mlx_delete_texture(mlx->tex[WE]), true);
	return (false);
}

int	main(void)
{
	t_mlx	mlx;

	mlx = (t_mlx){0};
	mlx.win = mlx_init(800, 600, "uowfemistaim", false);
	if (mlx.win == NULL)
		return (puts(mlx_strerror(mlx_errno)), 1);
	mlx.img = mlx_new_image(mlx.win, 800, 600);
	if (mlx.img == NULL)
		return (puts(mlx_strerror(mlx_errno)), mlx_terminate(mlx.win), 2);
	if (load_textures(&mlx))
		return (mlx_delete_image(mlx.win, mlx.img), mlx_terminate(mlx.win), 3);
	g_player_angle = start_looking_fix(90);
	g_dir_x = cos(RAD_1 * g_player_angle);
	g_dir_y = sin(RAD_1 * g_player_angle);
	mlx_key_hook(mlx.win, &keyboard, &mlx);
	mlx_cursor_hook(mlx.win, &mouse, &mlx);
	mlx_loop_hook(mlx.win, &render, &mlx);
	mlx_set_mouse_pos(mlx.win, 400, 300);
	mlx_set_cursor_mode(mlx.win, MLX_MOUSE_HIDDEN);
	mlx_image_to_window(mlx.win, mlx.img, 0, 0);
	mlx_loop(mlx.win);
	mlx_delete_image(mlx.win, mlx.img);
	mlx_terminate(mlx.win);
	return (0);
}
