#include "mlx_test.h"

void	movement_keys(t_mlx *mlx)
{
	if (mlx_is_key_down(mlx->win, MLX_KEY_W))
		change_pos(g_dir_x, g_dir_y);
	if (mlx_is_key_down(mlx->win, MLX_KEY_S))
		change_pos(-g_dir_x, -g_dir_y);
	if (mlx_is_key_down(mlx->win, MLX_KEY_D))
		change_pos(cos(RAD_1 * (g_player_angle + 90)) * 2,
			sin(RAD_1 * (g_player_angle + 90)) * 2);
	if (mlx_is_key_down(mlx->win, MLX_KEY_A))
		change_pos(-cos(RAD_1 * (g_player_angle + 90)) * 2,
			-sin(RAD_1 * (g_player_angle + 90)) * 2);
}

void	keyboard(mlx_key_data_t data, void *var)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)var;
	if (data.key == MLX_KEY_ESCAPE)
		mlx_close_window(mlx->win);
	if (mlx_is_key_down(mlx->win, MLX_KEY_LEFT))
	{
		g_player_angle -= ROT_ANG;
		if (g_player_angle < 0)
			g_player_angle = 360 + g_player_angle;
	}
	if (mlx_is_key_down(mlx->win, MLX_KEY_RIGHT))
		g_player_angle = (int)(g_player_angle + ROT_ANG) % 360;
	g_dir_x = cos(g_player_angle * RAD_1);
	g_dir_y = sin(g_player_angle * RAD_1);
	if (data.key == MLX_KEY_L && data.action == MLX_RELEASE)
		toggle_mouse(mlx);
	else
		movement_keys(mlx);
}
