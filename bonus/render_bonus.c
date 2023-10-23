/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adantas- <adantas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:59:19 by adantas-          #+#    #+#             */
/*   Updated: 2023/10/23 11:59:26 by adantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void	draw_background(t_mlx *mlx)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT_2)
				mlx_put_pixel(mlx->img, x, y, mlx->ceil);
			else
				mlx_put_pixel(mlx->img, x, y, mlx->floor);
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
			if (ft_strchr("1 ", (*getter_map())[map_y][map_x]))
				mlx_put_pixel(mlx->img, x, y, 0xFFA500FF);
			else
				mlx_put_pixel(mlx->img, x, y, CYAN);
			++x;
		}
		++y;
	}
}

void	draw_player(t_mlx *mlx)
{
	static const int	size = SIZE >> 2;
	const int			limit_y = (int)(*getter_player_y()) + size;
	const int			limit_x = (int)(*getter_player_x()) + size;
	int					x;
	int					y;

	y = (int)(*getter_player_y()) - size;
	while (y < limit_y)
	{
		x = (int)(*getter_player_x()) - size;
		while (x < limit_x)
		{
			if (y < 0 || x < 0)
				break ;
			mlx_put_pixel(mlx->img, x, y, BLACK);
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

	dist_x = *getter_dir_x() * DIR_SIZE;
	dist_y = *getter_dir_y() * DIR_SIZE;
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
		mlx_put_pixel(mlx->img, x0, y0, BLACK);
		x0 += dist_x;
		y0 += dist_y;
	}
}

void	render(void *var)
{
	t_mlx	*mlx;
	int		i;
	int		j;

	mlx = (t_mlx *)var;
	draw_background(mlx);
	cast_rays(mlx, -1, SIZE * WIDTH);
	i = 0;
	while ((*getter_map())[i] != NULL)
	{
		j = 0;
		while ((*getter_map())[i][j] != '\0')
		{
			draw_map(mlx, j, i);
			++j;
		}
		++i;
	}
	draw_direction(mlx, *getter_player_x(), *getter_player_y());
	draw_player(mlx);
}
