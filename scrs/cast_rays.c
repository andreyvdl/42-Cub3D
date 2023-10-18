#include "includes/mlx_test.h"

void	update_distance(double *x, double *y, double *ray, double *off)
{
	int	map[2];
	int	map_height;
	int	map_width;

	map_width = ft_strlen(**g_map());
	map_height = ft_matrixlen(*g_map());
	while (1)
	{
		map[X] = (int)(ray[X] / SIZE);
		map[Y] = (int)(ray[Y] / SIZE);
		if (map[X] < 0 || map[Y] < 0 || map[X] > map_width
			|| map[Y] > map_height || *g_map()[map[Y]][map[X]] == '1')
		{
			*x = ray[X];
			*y = ray[Y];
			break ;
		}
		ray[X] += off[X];
		ray[Y] += off[Y];
	}
}

double	cost_y_ray_distance(double *x, double *y, double tangent, \
							double ray_angle)
{
	double	off[2];
	double	ray[2];

	if (ray_angle > M_PI)
	{
		ray[Y] = ((int)(*getter_player_y() / SIZE) * SIZE) - 0.00001;
		ray[X] = (*getter_player_y() - ray[Y]) * tangent + *getter_player_x();
		off[Y] = -SIZE;
		off[X] = -off[Y] * tangent;
	}
	if (ray_angle < M_PI)
	{
		ray[Y] = ((int)(*getter_player_y() / SIZE) * SIZE) + SIZE;
		ray[X] = (*getter_player_y() - ray[Y]) * tangent + *getter_player_x();
		off[Y] = SIZE;
		off[X] = -off[Y] * tangent;
	}
	if (ray_angle == 0 || ray_angle == (double)M_PI)
	{
		ray[X] = *getter_player_x();
		ray[Y] = *getter_player_y();
	}
	update_distance(x, y, ray, off);
	return (pythagoras(*getter_player_x(), *getter_player_y(), ray[X], ray[Y]));
}

double	cost_x_ray_distance(double *x, double *y, double tangent, \
							double ray_angle)
{
	double	off[2];
	double	ray[2];

	if (ray_angle > RAD_90 && ray_angle < RAD_270)
	{
		ray[X] = ((int)(*getter_player_x() / SIZE) * SIZE) - 0.00001;
		ray[Y] = (*getter_player_x() - ray[X]) * tangent + *getter_player_y();
		off[X] = -SIZE;
		off[Y] = -off[X] * tangent;
	}
	if (ray_angle < RAD_90 || ray_angle > RAD_270)
	{
		ray[X] = ((int)(*getter_player_x() / SIZE) * SIZE) + SIZE;
		ray[Y] = (*getter_player_x() - ray[X]) * tangent + *getter_player_y();
		off[X] = SIZE;
		off[Y] = -off[X] * tangent;
	}
	if (ray_angle == (double)RAD_90 || ray_angle == (double)RAD_270)
	{
		ray[X] = *getter_player_x();
		ray[Y] = *getter_player_y();
	}
	update_distance(x, y, ray, off);
	return (pythagoras(*getter_player_x(), *getter_player_y(), ray[X], ray[Y]));
}

uint32_t	tex_to_col(mlx_texture_t *tex, int x, int y)
{
	uint8_t	*ptr;

	ptr = &tex->pixels[(y * tex->width + x) * tex->bytes_per_pixel];
	return (ptr[R] << 24 | ptr[G] << 16 | ptr[B] << 8 | ptr[A]);
	// return ((*ptr)++ << 24 | (*ptr)++ << 16 | (*ptr)++ << 8 | *ptr); // ataque epiletico
}

void	draw_wall(t_mlx *mlx, double height, int init, int ray_x, \
					mlx_texture_t *tex)
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
		tex_off = (height - 300);
		height = 300;
	}
	y_min = 300 - height;
	y_max = 300 + height;
	tex_y = tex_off * inc_tex;
	while (y_max >= y_min)
	{
		mlx_put_pixel(mlx->img, init, y_min, \
						tex_to_col(tex, ray_x, tex_y));
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
	double	fisheye; // passar o fisheye pra fora
	double	ray_inc;

	ray_ang = RAD_1 * (*getter_player_ang() - fov / 2.0);
	ray_inc = 0.002; // n pergunta como cheguei nesse valor, foi so tentativa e erro // RAD_360 / 3200; // 800 vezes 4
	for (int px = 0; px < 800; ++px)
	{
		ray_ang = rad_overflow(ray_ang);
		dist[Y] = cost_y_ray_distance(&x[Y], &y[Y], 1 / -tan(ray_ang), ray_ang);
		dist[X] = cost_x_ray_distance(&x[X], &y[X], -tan(ray_ang), ray_ang);
		fisheye = fisheye_fix(ray_ang);
		if (dist[Y] < dist[X])
		{
			if (ray_ang >= M_PI && ray_ang <= RAD_360)
				draw_wall(mlx, (SIZE * 800) / (dist[Y] * fisheye), px, (int)(x[Y] * SIZE) % 64, mlx->tex[NO]);
			else
				draw_wall(mlx, (SIZE * 800) / (dist[Y] * fisheye), px, 63 - (int)(x[Y] * SIZE) % 64, mlx->tex[SO]);
		}
		else
		{
			if (ray_ang >= RAD_90 && ray_ang <= RAD_270)
				draw_wall(mlx, (SIZE * 800) / (dist[X] * fisheye), px, 63 - (int)(y[X] * SIZE) % 64, mlx->tex[WE]);
			else
				draw_wall(mlx, (SIZE * 800) / (dist[X] * fisheye), px, (int)(y[X] * SIZE) % 64, mlx->tex[EA]);
		}
		ray_ang += ray_inc;
	}
}
