/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleite-s <rleite-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:04:42 by adantas-          #+#    #+#             */
/*   Updated: 2023/10/19 11:09:00 by rleite-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

uint32_t	tex_to_col(mlx_texture_t *tex, int x, int y)
{
	uint8_t	*ptr;

	ptr = &tex->pixels[(y * tex->width + x) * tex->bytes_per_pixel];
	return (ptr[R] << 24 | ptr[G] << 16 | ptr[B] << 8 | ptr[A]);
}

void	draw_wall(t_mlx *mlx, t_wall wall, mlx_texture_t *tex)
{
	int		y_min;
	int		y_max;
	double	tex_y;
	double	inc_tex;
	double	tex_off;

	if (tex == mlx->tex[SO] || tex == mlx->tex[EA])
		wall.ray_x = 63 - wall.ray_x;
	inc_tex = 63.0 / wall.height * 0.5;
	tex_off = 0;
	if (wall.height > 300)
	{
		tex_off = (wall.height - 300);
		wall.height = 300;
	}
	y_min = 300 - wall.height;
	y_max = 300 + wall.height;
	tex_y = tex_off * inc_tex;
	while (y_max >= y_min)
	{
		mlx_put_pixel(mlx->img, wall.init, y_min, \
						tex_to_col(tex, wall.ray_x, tex_y));
		tex_y += inc_tex;
		++y_min;
	}
}
