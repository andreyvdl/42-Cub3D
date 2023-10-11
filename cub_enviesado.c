#include "MLX42/include/MLX42/MLX42.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#define SIZE 8
#define ROT_ANG 1
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
	"1111111111111111",
	"1000000000000001",
	"1000000000000001",
	"1001100000011001",
	"1001100000011001",
	"1000000000000001",
	"1000000000000001",
	"1000000000000001",
	"1000000000000001",
	"1001100000011001",
	"1001100000011001",
	"1000000000000001",
	"1000000000000001",
	"1111111111111111",
	NULL
};
double		g_player_x = SIZE * 1.5;
double		g_player_y = SIZE * 1.5;
int	 		g_player_angle;
double		g_dir_x;
double		g_dir_y;

typedef struct s_mlx
{
	mlx_image_t		*tex_img[4];
	mlx_texture_t	*tex;
	mlx_image_t		*img;
	mlx_t			*win;
	bool			m_cntl;
}	t_mlx;

double	deg_to_rad(int deg)
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
	const int	limit_y = map_y * SIZE + SIZE;
	const int	limit_x = map_x * SIZE + SIZE;
	int			x;
	int			y;

	y = map_y * SIZE;
	while (y < limit_y)
	{
		x = map_x * SIZE;
		while (x < limit_x)
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

void	draw_player(t_mlx *mlx)
{
	static const int	size = SIZE >> 2;
	const int			limit_y = (int)g_player_y + size;
	const int			limit_x = (int)g_player_x + size;
	int					x;
	int					y;

	y = (int)g_player_y - size;
	while (y < limit_y)
	{
		x = (int)g_player_x - size;
		while (x < limit_x)
		{
			if (y < 0 || x < 0)
				break ;
			mlx_put_pixel(mlx->img, x, y, YELLOW);
			++x;
		}
		++y;
	}
}

void	draw_direction(t_mlx *mlx, double x0, double y0)
{
	double	dist_x;
	double	dist_y;
	double	step;

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

/* void	draw_ray(t_mlx *mlx, double x0, double y0, double x1, double y1, uint32_t color)
{
	double	dist_x;
	double	dist_y;
	double	step;

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

double	pythagoras(double x0, double y0, double x1, double y1)
{
	return (sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0)));
}

#define H 0
#define W 1

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

double	cost_y_ray_distance(double *x, double *y, double tangent, double ray_angle)
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

double	cost_x_ray_distance(double *x, double *y, double tangent, double ray_angle)
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

void	draw_wall(t_mlx *mlx, double height, int width, int init, uint32_t color)
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

double	fisheye_fix(double ray_angle)
{
	double	fisheye;

	fisheye = deg_to_rad(g_player_angle) - ray_angle;
	if (fisheye < 0)
		fisheye += RAD_360;
	else if (fisheye > RAD_360)
		fisheye -= RAD_360;
	return (cos(fisheye));
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
	ray_ang = deg_to_rad(g_player_angle + (fov / 2));
	while (fov--)
	{
		dist[H] = (double)INT_MAX;
		dist[W] = (double)INT_MAX;
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

void	draw_aim(t_mlx *mlx)
{
	const int	x = 800 / 2;
	const int	y = 600 / 2;
	uint32_t	color;
	int			counter;

	if (g_player_angle < 45 || g_player_angle > 315)
		color = BLUE;
	else if (g_player_angle > 45 && g_player_angle < 135)
		color = PINK;
	else if (g_player_angle > 135 && g_player_angle < 225)
		color = CYAN;
	else if (g_player_angle > 225 && g_player_angle < 315)
		color = YELLOW;
	else
		color = WHITE;
	counter = 1;
	mlx_put_pixel(mlx->img, x, y, color);
	while (counter < 15)
	{
		mlx_put_pixel(mlx->img, x + counter, y, color);
		mlx_put_pixel(mlx->img, x - counter, y, color);
		mlx_put_pixel(mlx->img, x, y + counter, color);
		mlx_put_pixel(mlx->img, x, y - counter, color);
		++counter;
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
	draw_aim(mlx);
}

void	change_pos(double x, double y)
{
	if (g_player_x + x > 1 \
	&& g_map[(int)(g_player_y / SIZE)][(int)((g_player_x + x) / SIZE)] != '1')
		g_player_x += x;
	if (g_player_y + y > 1 \
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
	if (data.key == MLX_KEY_L && data.action == MLX_RELEASE)
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
	g_dir_x = cos(deg_to_rad(g_player_angle));
	g_dir_y = sin(deg_to_rad(g_player_angle));
	mlx_set_mouse_pos(mlx->win, 400, 300);
}

int	angle_fix(int angle)
{
	if (angle > 90)
		return (360 - angle);
	else
		return (90 - angle);
}

#define NO 0
#define SO 1
#define WE 2
#define EA 3

bool	load_textures(t_mlx *mlx)
{
	mlx->tex = mlx_load_png("NORTH.png");
	if (mlx->tex == NULL)
		return (puts(mlx_strerror(mlx_errno)), true);
	mlx->tex_img[NO] = mlx_texture_to_image(mlx->win, mlx->tex);
	mlx_delete_texture(mlx->tex);
	if (mlx->tex_img[NO] == NULL)
		return (puts(mlx_strerror(mlx_errno)), true);
	mlx->tex = mlx_load_png("SOUTH.png");
	if (mlx->tex == NULL)
		return (puts(mlx_strerror(mlx_errno)), mlx_delete_image(mlx->win, mlx->tex_img[NO]), true);
	mlx->tex_img[SO] = mlx_texture_to_image(mlx->win, mlx->tex);
	mlx_delete_texture(mlx->tex);
	if (mlx->tex_img[SO] == NULL)
		return (puts(mlx_strerror(mlx_errno)), mlx_delete_image(mlx->win, mlx->tex_img[NO]), true);
	mlx->tex = mlx_load_png("WEST.png");
	if (mlx->tex == NULL)
		return (puts(mlx_strerror(mlx_errno)), mlx_delete_image(mlx->win, mlx->tex_img[NO]), mlx_delete_image(mlx->win, mlx->tex_img[SO]), true);
	mlx->tex_img[WE] = mlx_texture_to_image(mlx->win, mlx->tex);
	mlx_delete_texture(mlx->tex);
	if (mlx->tex_img[WE] == NULL)
		return (puts(mlx_strerror(mlx_errno)), mlx_delete_image(mlx->win, mlx->tex_img[NO]), mlx_delete_image(mlx->win, mlx->tex_img[SO]), true);
	mlx->tex = mlx_load_png("EAST.png");
	if (mlx->tex == NULL)
		return (puts(mlx_strerror(mlx_errno)), mlx_delete_image(mlx->win, mlx->tex_img[NO]), mlx_delete_image(mlx->win, mlx->tex_img[SO]), mlx_delete_image(mlx->win, mlx->tex_img[WE]), true);
	mlx->tex_img[EA] = mlx_texture_to_image(mlx->win, mlx->tex);
	mlx_delete_texture(mlx->tex);
	if (mlx->tex_img[EA] == NULL)
		return (puts(mlx_strerror(mlx_errno)), mlx_delete_image(mlx->win, mlx->tex_img[NO]), mlx_delete_image(mlx->win, mlx->tex_img[SO]), mlx_delete_image(mlx->win, mlx->tex_img[WE]), true);
	return (false);
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
	if (load_textures(&mlx))
		return (mlx_delete_image(mlx.win, mlx.img), mlx_terminate(mlx.win), 3);
	g_player_angle = angle_fix(90);
	g_dir_x = cos(deg_to_rad(g_player_angle) * 5);
	g_dir_y = sin(deg_to_rad(g_player_angle) * 5);
	mlx_key_hook(mlx.win, &keyboard, &mlx);
	mlx_cursor_hook(mlx.win, &mouse, &mlx);
	mlx_loop_hook(mlx.win, &render, &mlx);
	mlx_set_mouse_pos(mlx.win, 400, 300);
	mlx_set_cursor_mode(mlx.win, MLX_MOUSE_HIDDEN);
	mlx_image_to_window(mlx.win, mlx.img, 0, 0);
	// mlx_image_to_window(mlx.win, mlx.tex_img[NO], 336, 86);
	// mlx_image_to_window(mlx.win, mlx.tex_img[SO], 336, 450);
	// mlx_image_to_window(mlx.win, mlx.tex_img[WE], 136, 236);
	// mlx_image_to_window(mlx.win, mlx.tex_img[EA], 600, 236);
	mlx_loop(mlx.win);
	mlx_delete_image(mlx.win, mlx.img);
	mlx_terminate(mlx.win);
	return (0);
}
