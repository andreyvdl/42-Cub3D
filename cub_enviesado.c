#include "MLX42/include/MLX42/MLX42.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <float.h> // PQ OS LIMITES DO FLOAT ESTAO AQUI E N NA LIMITS??????????

#define SIZE 16
#define ROT_ANG 2
#define RAD_1 0.01745329
#define RED 0xFF0000FF
#define GREEN 0x00FF00FF
#define BLUE 0x0000FFFF
#define WHITE 0xFFFFFFFF
#define BLACK 0x000000FF
#define YELLOW 0xFFFF00FF
#define CYAN 0x00FFFFFF
#define PINK 0xFF00FFFF

float	g_player_x = SIZE * 1.5; // posição inicial do player
float	g_player_y = SIZE * 1.5;
int	 	g_player_angle;
float	g_dir_x;
float	g_dir_y;

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

float	deg_to_rad(int deg)
{
	return (deg * M_PI / 180);
}

// loop que desenha o fundo da tela
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

void	draw_map(t_mlx *mlx)
{
	for (int y = 0; g_map[y]; ++y) {
		for (int x = 0; g_map[y][x]; ++x) {
			for (int i = y * SIZE + 1; i < y * SIZE + SIZE ; ++i) {
				for (int j = x * SIZE + 1; j < x * SIZE + SIZE; ++j) {
					if (g_map[y][x] == '1')
						mlx_put_pixel(mlx->img, j, i, WHITE);
					else
						mlx_put_pixel(mlx->img, j, i, BLACK);
				}
			}
		}
	}
}

//desenha o player
void	draw_player(t_mlx *mlx)
{
	for (int i = g_player_y - 2; i < g_player_y + 2; ++i) {
		for (int j = g_player_x - 2; j < g_player_x + 2; ++j) {
			if (i < 0 || j < 0)
				break ;
			mlx_put_pixel(mlx->img, j, i, YELLOW);
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

	dist_x = g_dir_x * SIZE;
	dist_y = g_dir_y * SIZE;
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
		mlx_put_pixel(mlx->img, x0, y0, YELLOW);
		x0 += dist_x;
		y0 += dist_y;
	}
}

void	draw_ray(t_mlx *mlx, float x0, float y0, float x1, float y1, uint32_t color)
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
}

float	pythagoras(float x0, float y0, float x1, float y1)
{
	return (sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0)));
}

// A original
/* void	cast_rays(t_mlx *mlx)
{
	int		ray, mapX, mapY, DoF;
	float	rayX, rayY, rayAng, xOff, yOff;
	float	dist_h, hx, hy;
	float	dist_v, vx, vy;

	rayAng = deg_to_rad(g_player_angle - 30);
	for (ray = 0; ray < 60; ray++) {
		dist_h = FLT_MAX;
		dist_v = FLT_MAX;
		if (rayAng < 0)
			rayAng += 2 * M_PI;
		if (rayAng > 2 * M_PI)
			rayAng -= 2 * M_PI;
		DoF = 0;
		// algoritmo para colisão vertical
		float aTan = -1 / tan(rayAng);
		if (rayAng > M_PI && rayAng < 2 * M_PI) {
			rayY = ((int)(g_player_y / SIZE) * SIZE) - 0.0001;
			rayX = (g_player_y - rayY) * aTan + g_player_x;
			yOff = -SIZE;
			xOff = -yOff * aTan;
		}
		if (rayAng < M_PI && (rayAng > 0 && rayAng < 3 * M_PI / 2)) {
			rayY = ((int)(g_player_y / SIZE) * SIZE) + SIZE;
			rayX = (g_player_y - rayY) * aTan + g_player_x;
			yOff = SIZE;
			xOff = -yOff * aTan;
		}
		if (rayAng == 0 || rayAng == (float)M_PI) {
			rayX = g_player_x;
			rayY = g_player_y;
			DoF = 8;
		}
		while (DoF < 8) {
			mapX = (int)(rayX / SIZE);
			mapY = (int)(rayY / SIZE);
			if (mapX < 0 || mapY < 0 || mapX > 7 || mapY > 7 ||g_map[mapY][mapX] == '1') {
				hx = rayX;
				hy = rayY;
				dist_h = pythagoras(g_player_x, g_player_y, rayX, rayY);
				break ;
			}
			rayX += xOff;
			rayY += yOff;
			DoF--;
		}
		// algoritimo para a colisão horizontal
		aTan = -tan(rayAng);
		if (rayAng > M_PI / 2 && rayAng < 3 * M_PI / 2) {
			rayX = ((int)(g_player_x / SIZE) * SIZE) - 0.0001;
			rayY = (g_player_x - rayX) * aTan + g_player_y;
			xOff = -SIZE;
			yOff = -xOff * aTan;
		}
		if (rayAng < M_PI / 2 || rayAng > 3 * M_PI / 2) {
			rayX = ((int)(g_player_x / SIZE) * SIZE) + SIZE;
			rayY = (g_player_x - rayX) * aTan + g_player_y;
			xOff = SIZE;
			yOff = -xOff * aTan;
		}
		if (rayAng == M_PI / 2 || rayAng == 3 * M_PI / 2) {
			rayX = g_player_x;
			rayY = g_player_y;
			DoF = 8;
		}
		while (DoF < 8) {
			mapX = (int)(rayX / SIZE);
			mapY = (int)(rayY / SIZE);
			if (mapX < 0 || mapY < 0 || mapX > 7 || mapY > 7 ||g_map[mapY][mapX] == '1') {
				vx = rayX;
				vy = rayY;
				dist_v = pythagoras(g_player_x, g_player_y, rayX, rayY);
				break;
			}
			rayX += xOff;
			rayY += yOff;
			DoF--;
		}
		if (dist_h < dist_v)
			draw_ray(mlx, g_player_x, g_player_y, hx, hy, RED);
		else
			draw_ray(mlx, g_player_x, g_player_y, vx, vy, GREEN);
		rayAng += RAD_1;
	}
}
*/

#define H 0
#define W 1

void	fake_moulinette(float *x, float *y, float *ray, float *off)
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

	if (rayAng > M_PI && rayAng < 2 * M_PI)
	{
		ray[H] = ((int)(g_player_y / SIZE) * SIZE) - 0.0001;
		ray[W] = (g_player_y - ray[H]) * aTan + g_player_x;
		off[H] = -SIZE;
		off[W] = -off[H] * aTan;
	}
	if (rayAng < M_PI && rayAng < 3 * M_PI / 2)
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
	fake_moulinette(x, y, ray, off);
	return (pythagoras(g_player_x, g_player_y, ray[W], ray[H]));
}


float	cost_x_ray_distance(float *x, float *y, float aTan, float rayAng)
{
	float	off[2];
	float	ray[2];

	if (rayAng > M_PI / 2 && rayAng < 3 * M_PI / 2)
	{
		ray[W] = ((int)(g_player_x / SIZE) * SIZE) - 0.0001;
		ray[H] = (g_player_x - ray[W]) * aTan + g_player_y;
		off[W] = -SIZE;
		off[H] = -off[W] * aTan;
	}
	if (rayAng < M_PI / 2 || rayAng > 3 * M_PI / 2)
	{
		ray[W] = ((int)(g_player_x / SIZE) * SIZE) + SIZE;
		ray[H] = (g_player_x - ray[W]) * aTan + g_player_y;
		off[W] = SIZE;
		off[H] = -off[W] * aTan;
	}
	if (rayAng == M_PI / 2 || rayAng == 3 * M_PI / 2)
	{
		ray[W] = g_player_x;
		ray[H] = g_player_y;
	}
	fake_moulinette(x, y, ray, off);
	return (pythagoras(g_player_x, g_player_y, ray[W], ray[H]));
}

void	draw_wall(t_mlx *mlx, float height, int thickness)
{
	if (height > 428)
		height = 428;
	for (int y = 128 + height; y < 428 - height; ++y) {
		for (int x = 0 + thickness; x < thickness * SIZE; ++x) {
			mlx_put_pixel(mlx->img, x + SIZE, y, CYAN);
		}
	}
}

void	cast_rays(t_mlx *mlx, int fov)
{
	float	ray_ang;
	float	dist[2];
	float	x[2];
	float	y[2];

	ray_ang = deg_to_rad(g_player_angle - (fov / 2));
	while (fov--)
	{
		dist[H] = FLT_MAX;
		dist[W] = FLT_MAX;
		if (ray_ang < 0)
			ray_ang += 2 * M_PI;
		if (ray_ang > 2 * M_PI)
			ray_ang -= 2 * M_PI;
		dist[H] = cost_y_ray_distance(&x[H], &y[H], -1 / tan(ray_ang), ray_ang);
		dist[W] = cost_x_ray_distance(&x[W], &y[W], -tan(ray_ang), ray_ang);
		if (dist[H] < dist[W])
		{
			draw_ray(mlx, g_player_x, g_player_y, x[H], y[H], RED);
			draw_wall(mlx, SIZE * 472 / dist[H], fov * SIZE);
		}
		else
		{
			draw_ray(mlx, g_player_x, g_player_y, x[W], y[W], GREEN);
			draw_wall(mlx, SIZE * 472 / dist[W], fov * SIZE);
		}
		ray_ang += RAD_1;
	}
}


void	render(void *var)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)var;
	draw_background(mlx);
	draw_map(mlx);
	cast_rays(mlx, 30);
	draw_player(mlx);
	draw_direction(mlx, g_player_x, g_player_y);
}

//changed to make player drift when facing a wall
void	change_pos(float x, float y)
{
	if (g_player_x + x > 0.9 \
	&& g_map[(int)(g_player_y / SIZE)][(int)((g_player_x + x) / SIZE )] != '1')
		g_player_x += x;
	if (g_player_y + y > 0.9 \
	&& g_map[(int)((g_player_y + y) / SIZE)][(int)(g_player_x / SIZE )] != '1')
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
	g_dir_x = cos(deg_to_rad(g_player_angle)); // altera a rotação do player,
	g_dir_y = sin(deg_to_rad(g_player_angle)); // permite andar livremente
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
