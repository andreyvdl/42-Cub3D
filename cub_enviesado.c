#include "MLX42/include/MLX42/MLX42.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 16
#define LITTLE_PI 3.14
#define PI M_PI

float g_player_x = 3 * SIZE;
float g_player_y = 3 * SIZE;
float g_player_angle;
float g_dir_x;
float g_dir_y;

typedef struct s_mlx
{
	mlx_t		*win;
	mlx_image_t	*img;
}	t_mlx;

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

void	draw_background(t_mlx *mlx)
{
	// loop que desenha o fundo da tela
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

void	draw_map(t_mlx *mlx)
{
	for (int y = 0; g_map[y]; ++y) {
		for (int x = 0; g_map[y][x]; ++x) { // esses dois for olham o mapa
			for (int i = y * 32 + 1; i < y * 32 + 32 ; ++i) {
				for (int j = x * 32 + 1; j < x * 32 + 32; ++j) { // esses definem o limite do que vão desenhar
					if (g_map[y][x] == '1')
						mlx_put_pixel(mlx->img, j, i, 0xFFFFFFFF);
					else
						mlx_put_pixel(mlx->img, j, i, 0x000000FF);
				}
			}
		}
	}
}

void	draw_player(t_mlx *mlx)
{
	for (int i = g_player_y - 4; i < g_player_y + 4; ++i) {
		for (int j = g_player_x - 4; j < g_player_x + 4; ++j) {
			mlx_put_pixel(mlx->img, j, i, 0xFFFF00FF);
		}
	}
}

void	draw_direction(t_mlx *mlx) // basicamente o DDA
{
	float	dist_x;
	float	dist_y;
	float	x;
	float	y;
	float	step;

	dist_x = g_dir_x * 5 + g_player_x - g_player_x;
	dist_y = g_dir_y * 5 + g_player_y - g_player_y;
	if (fabs(dist_x) > fabs(dist_y))
		step = fabs(dist_x);
	else
		step = fabs(dist_y);
	dist_x /= step;
	dist_y /= step;
	x = g_player_x;
	y = g_player_y;
	for (int i = 0; i <= step; ++i) {
		mlx_put_pixel(mlx->img, (int)x, (int)y, 0xFF0000FF);
		x += dist_x;
		y += dist_y;
	}
}

void	draw_ray(t_mlx *mlx)
{
	float	ray_y;
	float	ray_x;
	float	ray_offset_x;
	float	ray_offset_y;
	int		depth_of_field;
	int		map_x;
	int		map_y;
	int		map_point;

	depth_of_field = 0;
	for (int rays = 0; rays < 1; ++rays) {
		if (g_player_angle > M_PI)
		{
			ray_y = g_player_y / 64 - 0.0001;
			ray_x = g_player_y - ray_y * (-1 / tan(g_player_angle)) + g_player_x;
			ray_offset_y = -64;
			ray_offset_x = ray_offset_y * (-1 / tan(g_player_angle));
		}
		if (g_player_angle < M_PI)
		{
			ray_y = g_player_y / 64 + 64;
			ray_x = g_player_y - ray_y * (-1 / tan(g_player_angle)) + g_player_x;
			ray_offset_y = 64;
			ray_offset_x = ray_offset_y * (-1 / tan(g_player_angle));
		}
		if (g_player_angle == 0) // precisa adicionar (|| g_player_angle == M_PI)
		{
			ray_x = g_player_x;
			ray_y = g_player_y;
			depth_of_field = 8;
		}
		while (depth_of_field < 8)
		{
			map_x = ray_x / 64;
			map_y = ray_y / 64;
			map_point = map_y * 8 + map_x; // 8 pq é o tamanho do mapa
			if (map_point < 8 * 8 && g_map[map_point] == '1') // mapa dele é plano, tem q converter isso pra matriz
		}
	}
}

void	render(void *var)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)var;
	draw_background(mlx);
	draw_map(mlx);
	draw_player(mlx);
	draw_direction(mlx);
	draw_ray(mlx);
	mlx_image_to_window(mlx->win, mlx->img, 0, 0);
}

void	keyboard(mlx_key_data_t data, void *var)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)var;
	if (data.key == MLX_KEY_A && data.action > MLX_RELEASE)
	{
		g_player_angle -= 0.1;
		if (g_player_angle < 0)
			g_player_angle += 2 * M_PI;
		g_dir_x = cos(g_player_angle) * 5;
		g_dir_y = sin(g_player_angle) * 5;
	}
	else if (data.key == MLX_KEY_D && data.action > MLX_RELEASE)
	{
		g_player_angle += 0.1;
		if (g_player_angle > 2 * M_PI)
			g_player_angle -= 2 * M_PI;
		g_dir_x = cos(g_player_angle) * 5;
		g_dir_y = sin(g_player_angle) * 5;
	}
	else if (data.key == MLX_KEY_W && data.action > MLX_RELEASE)
	{
		g_player_x += g_dir_x;
		g_player_y += g_dir_y;
	}
	else if (data.key == MLX_KEY_S && data.action > MLX_RELEASE)
	{
		g_player_y -= g_dir_y;
		g_player_x -= g_dir_x;
	}
	else if (data.key == MLX_KEY_ESCAPE && data.action == MLX_PRESS)
		mlx_close_window(mlx->win);
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
	g_player_angle = -(M_PI / 2);
	g_dir_x = cos(g_player_angle) * 5;
	g_dir_y = sin(g_player_angle) * 5;
	mlx_key_hook(mlx.win, &keyboard, &mlx);
	mlx_loop_hook(mlx.win, &render, &mlx);
	mlx_loop(mlx.win);
	mlx_terminate(mlx.win);
	return (0);
}
