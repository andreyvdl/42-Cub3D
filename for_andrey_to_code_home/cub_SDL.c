#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <stdbool.h>

/* gcc -Wall -Wextra -Werror cub_SDL.c -lSDL2 -lm */

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

typedef struct s_sdl {
	SDL_Window		*win;
	SDL_Renderer	*ren;
}				t_sdl;

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
void	draw_background(t_sdl *sdl)
{
	int	y;
	int	x;

	y = 0;
	while (y < 600)
	{
		x = 0;
		while (x < 800)
		{
			if (y < 300) {
				SDL_SetRenderDrawColor(sdl->ren, 0x88, 0x88, 0x88, 0xFF);
				SDL_RenderDrawPoint(sdl->ren, x, y);
			}
			else {
				SDL_SetRenderDrawColor(sdl->ren, 0x44, 0x44, 0x44, 0xFF);
				SDL_RenderDrawPoint(sdl->ren, x, y);
			}
			++x;
		}
		++y;
	}
}

void	draw_map(t_sdl *sdl)
{
	for (int y = 0; g_map[y]; ++y) {
		for (int x = 0; g_map[y][x]; ++x) {
			for (int i = y * SIZE + 1; i < y * SIZE + SIZE ; ++i) {
				for (int j = x * SIZE + 1; j < x * SIZE + SIZE; ++j) {
					if (g_map[y][x] == '1') {
						SDL_SetRenderDrawColor(sdl->ren, 0xFF, 0xFF, 0xFF, 0xFF);
						SDL_RenderDrawPoint(sdl->ren, j, i);
					}
					else {
						SDL_SetRenderDrawColor(sdl->ren, 0, 0, 0, 0xFF);
						SDL_RenderDrawPoint(sdl->ren, j, i);
					}
				}
			}
		}
	}
}

//desenha o player
void	draw_player(t_sdl *sdl)
{
	SDL_SetRenderDrawColor(sdl->ren, 0xFF, 0xFF, 0, 0xFF);
	for (int y = g_player_y - 2; y < g_player_y + 2; ++y) {
		for (int x = g_player_x - 2; x < g_player_x + 2; ++x) {
			if (y < 0 || x < 0)
				break ;
			SDL_RenderDrawPoint(sdl->ren, x, y);
		}
	}
}

//desenha a linha reta da direção do player
// o algoritmo é o DDA
void	draw_direction(t_sdl *sdl, float x0, float y0)
{
	float	dist_x;
	float	dist_y;
	float	step;

	SDL_SetRenderDrawColor(sdl->ren, 0xFF, 0xFF, 0, 0xFF);
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
		SDL_RenderDrawPoint(sdl->ren, x0, y0);
		x0 += dist_x;
		y0 += dist_y;
	}
}

void	draw_ray(t_sdl *sdl, float x0, float y0, float x1, float y1, uint32_t color)
{
	float	dist_x;
	float	dist_y;
	float	step;

	SDL_SetRenderDrawColor(sdl->ren, color >> 24, (color << 8) >> 24, (color << 16) >> 24, (color << 24) >> 24);
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
		SDL_RenderDrawPoint(sdl->ren, x0, y0);
		x0 += dist_x;
		y0 += dist_y;
	}
}

float	pythagoras(float x0, float y0, float x1, float y1)
{
	return (sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0)));
}

// A original
/* void	cast_rays(t_sdl *mlx)
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

void	draw_wall(t_sdl *sdl, float height, int thickness, int start_x, uint32_t color)
{
	SDL_SetRenderDrawColor(sdl->ren, color >> 24, (color << 8) >> 24, (color << 16) >> 24, (color << 24) >> 24);
	printf("height: %f\n", height);
	if (height > 320)
		height = 320;
	printf("height: %f\n", height);
	// algo de errado não está certo
	for (int y = 128 + height; y < 600 - height; ++y) {
		for (int x = start_x; x < start_x + thickness; ++x)
			SDL_RenderDrawPoint(sdl->ren, x, y);
	}
}

void	cast_rays(t_sdl *sdl, int fov)
{
	float	ray_ang;
	float	dist[2];
	float	x[2];
	float	y[2];
	int		thickness;
	int		start_x;
	float	fisheye_fix;

	thickness = 800.0 / fov;
	start_x = 800 - thickness;
	ray_ang = deg_to_rad(g_player_angle + (fov / 2));
	while (fov--)
	{
		dist[H] = (float)INT_MAX;
		dist[W] = (float)INT_MAX;
		if (ray_ang < 0)
			ray_ang += 2 * M_PI;
		if (ray_ang > 2 * M_PI)
			ray_ang -= 2 * M_PI;
		dist[H] = cost_y_ray_distance(&x[H], &y[H], 1 / -tan(ray_ang), ray_ang);
		dist[W] = cost_x_ray_distance(&x[W], &y[W], -tan(ray_ang), ray_ang);
		if (fov == 0)
		{
			thickness += start_x;
			start_x = 0;
		}
		fisheye_fix = deg_to_rad(g_player_angle) - ray_ang;
		if (fisheye_fix < 0)
			fisheye_fix += 2 * M_PI;
		else if (fisheye_fix > 2 * M_PI)
			fisheye_fix -= 2 * M_PI;
		if (dist[H] < dist[W])
		{
			draw_ray(sdl, g_player_x, g_player_y, x[H], y[H], RED);
			// a formula do vídeo não funciona passa o float direto
			// draw_wall(mlx, dist[H] / (SIZE * 800), thickness, start_x, RED);
			draw_wall(sdl, dist[H] * cos(fisheye_fix), thickness, start_x, RED - (int)dist[H]);
		}
		else
		{
			draw_ray(sdl, g_player_x, g_player_y, x[W], y[W], GREEN);
			// draw_wall(mlx, (SIZE * 800) / dist[W] , thickness, start_x, GREEN);
			draw_wall(sdl, dist[W] * cos(fisheye_fix), thickness, start_x, GREEN - (int)dist[W]);
		}
		start_x -= thickness;
		ray_ang -= RAD_1;
	}
}

void	sdl_loop(t_sdl *sdl) {
	SDL_Event	event;
	bool		run;

	run = true;
	while (run) {
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT)
				run = false;
		}
		SDL_SetRenderDrawColor(sdl->ren, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(sdl->ren);
		draw_background(sdl);
		draw_map(sdl);
		cast_rays(sdl, 80);
		draw_player(sdl);
		draw_direction(sdl, g_player_x, g_player_y);
		SDL_RenderPresent(sdl->ren);
	}
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

/* void	keyboard(mlx_key_data_t data, void *var)
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
} */

int	main(void)
{
	t_sdl	sdl;

	if (SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO) < 0) { 
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return (1);
	}
	sdl.win = SDL_CreateWindow("cub", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
	if (sdl.win == NULL) {
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return (2);
	}
	sdl.ren = SDL_CreateRenderer(sdl.win, -1, SDL_RENDERER_ACCELERATED);
	if (sdl.ren == NULL) {
		printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		return (3);
	}
	g_player_angle = 0; // precisa ser negativo pra inverter o sentido
	g_dir_x = cos(deg_to_rad(g_player_angle) * 5);
	g_dir_y = sin(deg_to_rad(g_player_angle) * 5);
	sdl_loop(&sdl);
	SDL_DestroyRenderer(sdl.ren);
	SDL_DestroyWindow(sdl.win);
	SDL_Quit();
	return (0);
}
