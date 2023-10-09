#include "MLX42/include/MLX42/MLX42.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#define SIZE 8
#define ROT_ANG 3
#define RAD_1 0.0174532925199
#define RAD_90 1.57079632679
#define RAD_270 4.71238898037
#define RAD_360 6.28318530716
#define RED 0xFF0000FF
#define GREEN 0x00FF00FF
#define BLUE 0x0000FFFF
#define WHITE 0xFFFFFFFF
#define BLACK 0x000000FF
#define YELLOW 0xFFFF00FF
#define CYAN 0x00FFFFFF
#define PINK 0xFF00FFFF

const char	*g_map[] = {
	"11111111",
	"10000001",
	"10000001",
	"10000001",
	"10000001",
	"10011001",
	"11000011",
	"11111111",
	NULL
};
float		g_player_x = SIZE * 1.5;
float		g_player_y = SIZE * 1.5;
int	 		g_player_angle;
float		g_dir_x;
float		g_dir_y;

typedef struct s_mlx
{
	mlx_t		*win;
	mlx_image_t	*img;
}	t_mlx;

float	deg_to_rad(int deg)
{
	return (deg * RAD_1);
}

void	draw_background(t_mlx *mlx)
{
	int	y;
	int	x;

	y = 0;
	while (y < 600)
	{
		x = 0;
		while (x < 800)
		{
			if (y < 300)
				mlx_put_pixel(mlx->img, x, y, 0x888888FF);
			else
				mlx_put_pixel(mlx->img, x, y, 0x444444FF);
			++x;
		}
		++y;
	}
}

void	draw_map(t_mlx *mlx, int map_x, int map_y)
{
	int	x;
	int	y;

	y = map_y * SIZE;
	while (y < map_y * SIZE + SIZE)
	{
		x = map_x * SIZE;
		while (x < map_x * SIZE + SIZE)
		{
			if (g_map[map_y][map_x] == '1')
				mlx_put_pixel(mlx->img, x, y, WHITE);
			else
				mlx_put_pixel(mlx->img, x, y, BLACK);
			++x;
		}
		++y;
	}
}

//desenha o player
void	draw_player(t_mlx *mlx)
{
	int	x;
	int	y;

	y = (int)g_player_y - (SIZE >> 2);
	while (y < (int)g_player_y + (SIZE >> 2))
	{
		x = (int)g_player_x - (SIZE >> 2);
		while (x < (int)g_player_x + (SIZE >> 2))
		{
			if (y < 0 || x < 0)
				break ;
			mlx_put_pixel(mlx->img, x, y, YELLOW);
			++x;
		}
		++y;
	}
}

void	draw_direction(t_mlx *mlx, float x0, float y0)
{
	float	dist_x;
	float	dist_y;
	float	step;

	dist_x = g_dir_x * 8;
	dist_y = g_dir_y * 8;
	if (fabs(dist_x) > fabs(dist_y))
		step = fabs(dist_x);
	else
		step = fabs(dist_y);
	dist_x /= step;
	dist_y /= step;
	while ((int)step--)
	{
		if (x0 < 0 || y0 < 0)
			break ;
		mlx_put_pixel(mlx->img, x0, y0, CYAN);
		x0 += dist_x;
		y0 += dist_y;
	}
}

/* void	draw_ray(t_mlx *mlx, float x0, float y0, float x1, float y1, uint32_t color)
{
	float	dist_x;
	float	dist_y;
	float	step;

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

float	pythagoras(float x0, float y0, float x1, float y1)
{
	return (sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0)));
}

#define H 0
#define W 1

void	update_distance(float *x, float *y, float *ray, float *off)
{
	int	map[2];

	while (1)
	{
		map[W] = (int)(ray[W] / SIZE);
		map[H] = (int)(ray[H] / SIZE);
		if (map[W] < 0 || map[H] < 0 || map[W] > 7 || map[H] > 7
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

float	cost_y_ray_distance(float *x, float *y, float aTan, float rayAng)
{
	float	off[2];
	float	ray[2];

	if (rayAng > M_PI && rayAng < RAD_360)
	{
		ray[H] = ((int)(g_player_y / SIZE) * SIZE) - 0.0001;
		ray[W] = (g_player_y - ray[H]) * aTan + g_player_x;
		off[H] = -SIZE;
		off[W] = -off[H] * aTan;
	}
	if (rayAng < M_PI && rayAng < RAD_270)
	{
		ray[H] = ((int)(g_player_y / SIZE) * SIZE) + SIZE;
		ray[W] = (g_player_y - ray[H]) * aTan + g_player_x;
		off[H] = SIZE;
		off[W] = -off[H] * aTan;
	}
	if (rayAng == 0 || rayAng == (float)M_PI)
	{
		ray[W] = g_player_x;
		ray[H] = g_player_y;
	}
	update_distance(x, y, ray, off);
	return (pythagoras(g_player_x, g_player_y, ray[W], ray[H]));
}

float	cost_x_ray_distance(float *x, float *y, float aTan, float rayAng)
{
	float	off[2];
	float	ray[2];

	if (rayAng > RAD_90 && rayAng < RAD_270)
	{
		ray[W] = ((int)(g_player_x / SIZE) * SIZE) - 0.0001;
		ray[H] = (g_player_x - ray[W]) * aTan + g_player_y;
		off[W] = -SIZE;
		off[H] = -off[W] * aTan;
	}
	if (rayAng < RAD_90 || rayAng > RAD_270)
	{
		ray[W] = ((int)(g_player_x / SIZE) * SIZE) + SIZE;
		ray[H] = (g_player_x - ray[W]) * aTan + g_player_y;
		off[W] = SIZE;
		off[H] = -off[W] * aTan;
	}
	if (rayAng == (float)RAD_90 || rayAng == (float)RAD_270)
	{
		ray[W] = g_player_x;
		ray[H] = g_player_y;
	}
	update_distance(x, y, ray, off);
	return (pythagoras(g_player_x, g_player_y, ray[W], ray[H]));
}

void	draw_wall(t_mlx *mlx, float height, int width, int init, uint32_t color)
{
	int	y;
	int	x;
	int	length;

	if (height > 300)
		height = 300;
	y = 300;
	length = width + init;
	while ((int)height >= 0)
	{
		x = init;
		while (x < length)
		{
			mlx_put_pixel(mlx->img, x, y + height, color - 64);
			mlx_put_pixel(mlx->img, x, y - height, color - 64);
			++x;
		}
		--height;
	}
}

float	fisheye_fix(float ray_angle)
{
	float	fisheye;

	fisheye = deg_to_rad(g_player_angle) - ray_angle;
	if (fisheye < 0)
		fisheye += RAD_360;
	else if (fisheye > RAD_360)
		fisheye -= RAD_360;
	return (cos(fisheye));
}

void	cast_rays(t_mlx *mlx, int fov)
{
	float	ray_ang;
	float	dist[2];
	float	x[2];
	float	y[2];
	int		thickness;
	int		start_x;
	float	fisheye;

	thickness = 800.0 / fov;
	start_x = 800 - thickness;
	ray_ang = deg_to_rad(g_player_angle + (fov / 2));
	while (fov--)
	{
		dist[H] = (float)INT_MAX;
		dist[W] = (float)INT_MAX;
		if (ray_ang < 0)
			ray_ang += RAD_360;
		if (ray_ang > RAD_360)
			ray_ang -= RAD_360;
		dist[H] = cost_y_ray_distance(&x[H], &y[H], 1 / -tan(ray_ang), ray_ang);
		dist[W] = cost_x_ray_distance(&x[W], &y[W], -tan(ray_ang), ray_ang);
		if (fov == 0)
		{
			thickness += start_x;
			start_x = 0;
		}
		fisheye = fisheye_fix(ray_ang);
		if (dist[H] < dist[W])
		{
			// draw_ray(mlx, g_player_x, g_player_y, x[H], y[H], RED);
			draw_wall(mlx, (SIZE * 800) / (dist[H] * fisheye), thickness, start_x, RED - (int)dist[H]);
		}
		else
		{
			// draw_ray(mlx, g_player_x, g_player_y, x[W], y[W], GREEN);
			draw_wall(mlx, (SIZE * 800) / (dist[W] * fisheye), thickness, start_x, GREEN - (int)dist[W]);
		}
		start_x -= thickness;
		ray_ang -= RAD_1;
	}
}

void	render(void *var)
{
	t_mlx	*mlx;
	int		i;
	int		j;

	mlx = (t_mlx *)var;
	draw_background(mlx);
	cast_rays(mlx, 80);
	i = 0;
	while (g_map[i] != NULL)
	{
		j = 0;
		while (g_map[i][j] != '\0')
		{
			draw_map(mlx, j, i);
			++j;
		}
		++i;
	}
	draw_direction(mlx, g_player_x, g_player_y);
	draw_player(mlx);
}

void	change_pos(float x, float y)
{
	if (g_player_x + x > 0.9 \
	&& g_map[(int)(g_player_y / SIZE)][(int)((g_player_x + x) / SIZE)] != '1')
		g_player_x += x;
	if (g_player_y + y > 0.9 \
	&& g_map[(int)((g_player_y + y) / SIZE)][(int)(g_player_x / SIZE)] != '1')
		g_player_y += y;
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
	g_dir_x = cos(deg_to_rad(g_player_angle));
	g_dir_y = sin(deg_to_rad(g_player_angle));
	if (mlx_is_key_down(mlx->win, MLX_KEY_W))
		change_pos(g_dir_x, g_dir_y);
	if (mlx_is_key_down(mlx->win, MLX_KEY_S))
		change_pos(-g_dir_x, -g_dir_y);
	if (mlx_is_key_down(mlx->win, MLX_KEY_D))
		change_pos(cos(deg_to_rad(g_player_angle + 90)) * 2,
			sin(deg_to_rad(g_player_angle + 90)) * 2);
	if (mlx_is_key_down(mlx->win, MLX_KEY_A))
		change_pos(-cos(deg_to_rad(g_player_angle + 90)) * 2,
			-sin(deg_to_rad(g_player_angle + 90)) * 2);
}

int	main(void)
{
	t_mlx	mlx;

	mlx = (t_mlx){0};
	mlx.win = mlx_init(800, 600, "titulo", false);
	if (mlx.win == NULL)
		return (puts(mlx_strerror(mlx_errno)), 1);
	mlx.img = mlx_new_image(mlx.win, 800, 600);
	if (mlx.img == NULL)
		return (puts(mlx_strerror(mlx_errno)), mlx_terminate(mlx.win), 2);
	mlx_image_to_window(mlx.win, mlx.img, 0, 0);
	g_player_angle = 0; // precisa ser negativo pra inverter o sentido
	g_dir_x = cos(deg_to_rad(g_player_angle) * 5);
	g_dir_y = sin(deg_to_rad(g_player_angle) * 5);
	mlx_key_hook(mlx.win, &keyboard, &mlx);
	mlx_loop_hook(mlx.win, &render, &mlx);
	mlx_loop(mlx.win);
	mlx_terminate(mlx.win);
	return (0);
}
