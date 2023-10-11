#include "mlx_test.h"

void	toggle_mouse(t_mlx *mlx)
{
	if (mlx->m_cntl == true)
	{
		mlx_set_cursor_mode(mlx->win, MLX_MOUSE_HIDDEN);
		mlx->m_cntl = false;
	}
	else
	{
		mlx_set_cursor_mode(mlx->win, MLX_MOUSE_NORMAL);
		mlx->m_cntl = true;
	}
	mlx_set_mouse_pos(mlx->win, 400, 300);
}

void	mouse(double x_pos, double y_pos, void *var)
{
	t_mlx	*mlx;

	(void)y_pos;
	mlx = (t_mlx *)var;
	if (mlx->m_cntl == true)
		return ;
	if (x_pos < 400)
		g_player_angle -= ROT_ANG;
	else if (x_pos > 400)
		g_player_angle += ROT_ANG;
	g_dir_x = cos(RAD_1 * g_player_angle);
	g_dir_y = sin(RAD_1 * g_player_angle);
	mlx_set_mouse_pos(mlx->win, 400, 300);
}
