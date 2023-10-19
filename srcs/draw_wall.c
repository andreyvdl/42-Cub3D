/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adantas- <adantas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:04:42 by adantas-          #+#    #+#             */
/*   Updated: 2023/10/19 14:57:33 by adantas-         ###   ########.fr       */
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

	if (tex == mlx->tex[SO] || tex == mlx->tex[WE])
		wall.ray_x = 63 - wall.ray_x;
	inc_tex = 63.0 / wall.height * 0.5;
	tex_off = 0;
	if (wall.height > HEIGHT_2)
	{
		tex_off = (wall.height - HEIGHT_2);
		wall.height = HEIGHT_2;
	}
	y_min = HEIGHT_2 - wall.height;
	y_max = HEIGHT_2 + wall.height;
	tex_y = tex_off * inc_tex;
	while (y_max > y_min)
	{
		mlx_put_pixel(mlx->img, wall.init, y_min, \
						tex_to_col(tex, wall.ray_x, tex_y));
		tex_y += inc_tex;
		++y_min;
	}
}
