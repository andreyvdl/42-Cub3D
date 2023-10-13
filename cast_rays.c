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
		ray[H] = ((int)(g_player_y / SIZE) * SIZE) - 0.00001;
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
		ray[W] = ((int)(g_player_x / SIZE) * SIZE) - 0.00001;
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

uint32_t	tex_to_col(mlx_texture_t *tex, int x, int y)
{
	uint8_t	*ptr;

	ptr = &tex->pixels[(y * tex->width + x % 64) * tex->bytes_per_pixel];
	return (ptr[R] << 24 | ptr[G] << 16 | ptr[B] << 8 | ptr[A]);
}

void	draw_wall(t_mlx *mlx, double height, int init, mlx_texture_t *tex)
{
	int		y_min;
	int		y_max;
	double	tex_y;
	double	inc_tex;
	double	tex_off;

	inc_tex = 63.0 / height * 0.5;
	tex_off = 0;
	if (height > 300)
	{
		tex_off = (height - 300); // removi a divisão por 2 do vídeo
		height = 300;
	}
	y_min = 300 - height;
	y_max = 300 + height;
	tex_y = tex_off * inc_tex;
	while (y_max >= y_min)
	{
		mlx_put_pixel(mlx->img, init, y_min, \
						tex_to_col(tex, init, tex_y));
		tex_y += inc_tex;
		++y_min;
	}
}

void	cast_rays(t_mlx *mlx, int fov)
{
	double	dist[2];
	double	x[2];
	double	y[2];
	double	ray_ang;
	double	fisheye;
	double	ray_inc;

	ray_ang = RAD_1 * (g_player_angle - fov / 2.0);
	ray_inc = 0.002; // RAD_360 / 3200; // 800 vezes 4
	for (int px = 0; px < 800; ++px)
	{
		ray_ang = rad_overflow(ray_ang);
		dist[H] = (double)INT_MAX;
		dist[W] = (double)INT_MAX;
		dist[H] = cost_y_ray_distance(&x[H], &y[H], 1 / -tan(ray_ang), ray_ang);
		dist[W] = cost_x_ray_distance(&x[W], &y[W], -tan(ray_ang), ray_ang);
		fisheye = fisheye_fix(ray_ang);
		if (dist[H] < dist[W])
		{
			// draw_ray(mlx, g_player_x, g_player_y, x[H], y[H], RED);
			if (ray_ang >= M_PI && ray_ang <= RAD_360)
				draw_wall(mlx, (SIZE * 800) / (dist[H] * fisheye), px, mlx->tex[NO]);
			else
				draw_wall(mlx, (SIZE * 800) / (dist[H] * fisheye), px, mlx->tex[SO]);
		}
		else
		{
			// draw_ray(mlx, g_player_x, g_player_y, x[W], y[W], GREEN);
			if (ray_ang >= RAD_90 && ray_ang <= RAD_270)
				draw_wall(mlx, (SIZE * 800) / (dist[W] * fisheye), px, mlx->tex[WE]);
			else
				draw_wall(mlx, (SIZE * 800) / (dist[W] * fisheye), px, mlx->tex[EA]);
		}
		ray_ang += ray_inc;
	}
}
