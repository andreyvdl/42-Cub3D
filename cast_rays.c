#include "mlx_test.h"

void	update_distance(double *x, double *y, double *ray, double *off)
{
	int	map[2];

	while (1)
	{
		map[W] = (int)(ray[W] / SIZE);
		map[H] = (int)(ray[H] / SIZE);
		if (map[W] < 0 || map[H] < 0 || map[W] > 15 || map[H] > 13
			|| g_map[map[H]][map[W]] == '1')
		{
			*x = ray[W];
			*y = ray[H];
			break ;
		}
		ray[W] += off[W];
		ray[H] += off[H];
	}
}

double	cost_y_ray_distance(double *x, double *y, double tangent, \
							double ray_angle)
{
	double	off[2];
	double	ray[2];

	if (ray_angle > M_PI)
	{
		ray[H] = ((int)(g_player_y / SIZE) * SIZE) - 0.0001;
		ray[W] = (g_player_y - ray[H]) * tangent + g_player_x;
		off[H] = -SIZE;
		off[W] = -off[H] * tangent;
	}
	if (ray_angle < M_PI)
	{
		ray[H] = ((int)(g_player_y / SIZE) * SIZE) + SIZE;
		ray[W] = (g_player_y - ray[H]) * tangent + g_player_x;
		off[H] = SIZE;
		off[W] = -off[H] * tangent;
	}
	if (ray_angle == 0 || ray_angle == (double)M_PI)
	{
		ray[W] = g_player_x;
		ray[H] = g_player_y;
	}
	update_distance(x, y, ray, off);
	return (pythagoras(g_player_x, g_player_y, ray[W], ray[H]));
}

double	cost_x_ray_distance(double *x, double *y, double tangent, \
							double ray_angle)
{
	double	off[2];
	double	ray[2];

	if (ray_angle > RAD_90 && ray_angle < RAD_270)
	{
		ray[W] = ((int)(g_player_x / SIZE) * SIZE) - 0.0001;
		ray[H] = (g_player_x - ray[W]) * tangent + g_player_y;
		off[W] = -SIZE;
		off[H] = -off[W] * tangent;
	}
	if (ray_angle < RAD_90 || ray_angle > RAD_270)
	{
		ray[W] = ((int)(g_player_x / SIZE) * SIZE) + SIZE;
		ray[H] = (g_player_x - ray[W]) * tangent + g_player_y;
		off[W] = SIZE;
		off[H] = -off[W] * tangent;
	}
	if (ray_angle == (double)RAD_90 || ray_angle == (double)RAD_270)
	{
		ray[W] = g_player_x;
		ray[H] = g_player_y;
	}
	update_distance(x, y, ray, off);
	return (pythagoras(g_player_x, g_player_y, ray[W], ray[H]));
}

void	draw_wall(t_mlx *mlx, double height, int width, int init, \
					uint32_t color)
{
	int	y;
	int	x;
	int	length;

	if (height > 299)
		height = 299;
	y = 300;
	length = width + init;
	while ((int)height >= 0)
	{
		x = init;
		while (x < length)
		{
			mlx_put_pixel(mlx->img, x, y + height, color - 100);
			mlx_put_pixel(mlx->img, x, y - height, color - 100);
			++x;
		}
		--height;
	}
}

void	cast_rays(t_mlx *mlx, int fov)
{
	double	ray_ang;
	double	dist[2];
	double	x[2];
	double	y[2];
	int		thickness;
	int		start_x;
	double	fisheye;

	thickness = 800.0 / fov;
	start_x = 800 - thickness;
	ray_ang = RAD_1 * (g_player_angle + fov / 2);
	while (fov--)
	{
		dist[H] = (double)INT_MAX;
		dist[W] = (double)INT_MAX;
		ray_ang = rad_overflow(ray_ang);
		dist[H] = cost_y_ray_distance(&x[H], &y[H], 1 / -tan(ray_ang), ray_ang);
		dist[W] = cost_x_ray_distance(&x[W], &y[W], -tan(ray_ang), ray_ang);
		if (fov == 0)
		{ // needed for starting fov different to 100
			thickness += start_x;
			start_x = 0;
		}
		fisheye = fisheye_fix(ray_ang);
		if (dist[H] < dist[W])
		{
			// draw_ray(mlx, g_player_x, g_player_y, x[H], y[H], RED);
			draw_wall(mlx, (SIZE * 800) / (dist[H] * fisheye), thickness, \
						start_x, RED - (int)dist[H]);
		}
		else
		{
			// draw_ray(mlx, g_player_x, g_player_y, x[W], y[W], GREEN);
			draw_wall(mlx, (SIZE * 800) / (dist[W] * fisheye), thickness, \
						start_x, GREEN - (int)dist[W]);
		}
		start_x -= thickness;
		ray_ang -= RAD_1;
	}
}
