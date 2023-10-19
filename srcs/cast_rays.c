/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adantas- <adantas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:32:22 by adantas-          #+#    #+#             */
/*   Updated: 2023/10/19 15:00:09 by adantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void	update_distance(double *x, double *y, double *ray, double *off)
{
	int	map[2];
	int	map_height;
	int	map_width;

	map_width = ft_strlen(**getter_map());
	map_height = ft_matrixlen(*getter_map());
	while (1)
	{
		map[X] = (int)(ray[X] / SIZE);
		map[Y] = (int)(ray[Y] / SIZE);
		if (map[X] < 0 || map[Y] < 0 || map[X] > map_width - 1 || map[Y] > \
			map_height - 1 || (*getter_map())[map[Y]][map[X]] == '1')
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
		ray[Y] = ((int)(*getter_player_y() / SIZE)) * SIZE - 0.00001;
		ray[X] = (*getter_player_y() - ray[Y]) * tangent + *getter_player_x();
		off[Y] = -SIZE;
		off[X] = -off[Y] * tangent;
	}
	if (ray_angle < M_PI)
	{
		ray[Y] = (((int)(*getter_player_y() / SIZE)) * SIZE) + SIZE;
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
		ray[X] = ((int)(*getter_player_x() / SIZE)) * SIZE - 0.00001;
		ray[Y] = (*getter_player_x() - ray[X]) * tangent + *getter_player_y();
		off[X] = -SIZE;
		off[Y] = -off[X] * tangent;
	}
	if (ray_angle < RAD_90 || ray_angle > RAD_270)
	{
		ray[X] = ((int)(*getter_player_x() / SIZE)) * SIZE + SIZE;
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

mlx_texture_t	*texture_ternary(mlx_texture_t *cond1, mlx_texture_t *cond2,
									bool result)
{
	if (result)
		return (cond1);
	return (cond2);
}

void	cast_rays(t_mlx *mlx, int pixel, int width_sz)
{
	double	dist[2];
	double	x[2];
	double	y[2];
	double	ray_ang;
	double	ray_inc;

	ray_ang = RAD_1 * (*getter_player_ang() - FOV / 2.0);
	ray_inc = RAD_90 / WIDTH;
	while (++pixel < WIDTH)
	{
		ray_ang = rad_overflow(ray_ang);
		dist[Y] = cost_y_ray_distance(&x[Y], &y[Y], 1 / -tan(ray_ang), ray_ang);
		dist[X] = cost_x_ray_distance(&x[X], &y[X], -tan(ray_ang), ray_ang);
		if (dist[Y] < dist[X])
			draw_wall(mlx, (t_wall){width_sz / (dist[Y] * fisheye_fix(ray_ang) \
			), pixel, (int)(x[Y] * SIZE) % 64}, texture_ternary(mlx->tex[NO], \
			mlx->tex[SO], ray_ang >= M_PI && ray_ang <= RAD_360));
		else
			draw_wall(mlx, (t_wall){width_sz / (dist[X] * fisheye_fix(ray_ang) \
			), pixel, (int)(y[X] * SIZE) % 64}, texture_ternary(mlx->tex[WE], \
			mlx->tex[EA], ray_ang >= RAD_90 && ray_ang <= RAD_270));
		ray_ang += ray_inc;
	}
}
