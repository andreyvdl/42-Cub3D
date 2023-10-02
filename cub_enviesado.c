#include "MLX42/include/MLX42/MLX42.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 16
#define ROT_ANG 11

float g_player_x = 3 * SIZE; // posição inicial do player
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

float	deg_to_rad(float deg)
{
	return (-(deg * M_PI / 180));
}

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
			for (int i = y * SIZE + 1; i < y * SIZE + SIZE ; ++i) {
				for (int j = x * SIZE + 1; j < x * SIZE + SIZE; ++j) { // esses definem o limite do que vão desenhar
					if (g_map[y][x] == '1')
						mlx_put_pixel(mlx->img, j, i, 0x00FF00FF);
					else
						mlx_put_pixel(mlx->img, j, i, 0x0000FFFF);
				}
			}
		}
	}
}

	//desenha o player
void	draw_player(t_mlx *mlx)
{
	for (int i = g_player_y - 4; i < g_player_y + 4; ++i) {
		for (int j = g_player_x - 4; j < g_player_x + 4; ++j) {
			if (i < 0 || j < 0)
				break ;
			mlx_put_pixel(mlx->img, j, i, 0xFFFF00FF);
		}
	}
}

//desenha a linha reta da direção do player
// o algoritmo é o DDA
void	draw_direction(t_mlx *mlx, float x0, float y0)
{
	float	dist_x;
	float	dist_y;
	float	step;

	dist_x = g_dir_x * SIZE / 2; // multiplicação define a distancia do vetor
	dist_y = g_dir_y * SIZE / 2;
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
		mlx_put_pixel(mlx->img, x0, y0, 0xFFFF00FF);
		x0 += dist_x;
		y0 += dist_y;
	}
}

/* void	draw_ray(t_mlx *mlx) // WIP
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
} */

void	render(void *var)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)var;
	draw_background(mlx);
	draw_map(mlx);
	draw_player(mlx);
	draw_direction(mlx, g_player_x, g_player_y);
	// draw_ray(mlx);
}

void	change_pos(float x, float y)
{
	if (g_player_x + x > 0.9)
		g_player_x += x;
	if (g_player_y + y > 0.9)
		g_player_y += y;
}

void	keyboard(mlx_key_data_t data, void *var)
{
	t_mlx	*mlx;

	(void)data;
	mlx = (t_mlx *)var;
	if (mlx_is_key_down(mlx->win, MLX_KEY_LEFT))
	{
		g_player_angle -= ROT_ANG;
		if (g_player_angle < 0)
			g_player_angle += 359;
	}
	if (mlx_is_key_down(mlx->win, MLX_KEY_RIGHT))
		g_player_angle = (int)(g_player_angle + ROT_ANG) % 360;
	g_dir_x = cos(deg_to_rad(g_player_angle)) * 3; // altera a rotação do player,
	g_dir_y = sin(deg_to_rad(g_player_angle)) * 3; // permite andar livremente
	if (mlx_is_key_down(mlx->win, MLX_KEY_W))
		change_pos(g_dir_x, g_dir_y);
	if (mlx_is_key_down(mlx->win, MLX_KEY_S))
		change_pos(-g_dir_x, -g_dir_y);
	if (mlx_is_key_down(mlx->win, MLX_KEY_A))
		change_pos(cos(deg_to_rad(g_player_angle + 90)) * 3, sin(deg_to_rad(g_player_angle + 90)) * 3);
	if (mlx_is_key_down(mlx->win, MLX_KEY_D))
		change_pos(-cos(deg_to_rad(g_player_angle + 90)) * 3, -sin(deg_to_rad(g_player_angle + 90)) * 3);
	if (mlx_is_key_down(mlx->win, MLX_KEY_ESCAPE))
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
	mlx_image_to_window(mlx.win, mlx.img, 0, 0);
	g_player_angle = -90; // precisa ser negativo pra inverter o sentido
	g_dir_x = cos(deg_to_rad(g_player_angle)) * 3;
	g_dir_y = sin(deg_to_rad(g_player_angle)) * 3;
	mlx_key_hook(mlx.win, &keyboard, &mlx);
	mlx_loop_hook(mlx.win, &render, &mlx);
	mlx_loop(mlx.win);
	mlx_terminate(mlx.win);
	return (0);
}
