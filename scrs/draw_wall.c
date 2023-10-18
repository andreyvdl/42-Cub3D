/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adantas- <adantas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:04:42 by adantas-          #+#    #+#             */
/*   Updated: 2023/10/18 15:36:14 by adantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

uint32_t	tex_to_col(mlx_texture_t *tex, int x, int y)
{
	uint8_t	*ptr;

	ptr = &tex->pixels[(y * tex->width + x) * tex->bytes_per_pixel];
	return (ptr[R] << 24 | ptr[G] << 16 | ptr[B] << 8 | ptr[A]);
}

void	draw_wall(t_mlx *mlx, double height, int init, int ray_x, \
					mlx_texture_t *tex) // to fix
{
	int		y_min;
	int		y_max;
	double	tex_y;
	double	inc_tex;
	double	tex_off;

	if (tex == mlx->tex[SO] || tex == mlx->tex[EA])
		ray_x = 63 - ray_x;
	inc_tex = 63.0 / height * 0.5;
	tex_off = 0;
	if (height > 300)
	{
		tex_off = (height - 300);
		height = 300;
	}
	y_min = 300 - height;
	y_max = 300 + height;
	tex_y = tex_off * inc_tex;
	while (y_max >= y_min)
	{
		mlx_put_pixel(mlx->img, init, y_min, \
						tex_to_col(tex, ray_x, tex_y));
		tex_y += inc_tex;
		++y_min;
	}
}
