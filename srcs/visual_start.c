/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adantas- <adantas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:00:24 by adantas-, r       #+#    #+#             */
/*   Updated: 2023/10/18 16:59:33 by adantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

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

bool	load_textures(t_mlx *mlx)
{
	mlx->tex[NO] = mlx_load_png(mlx->attributes[NO]);
	mlx->tex[SO] = mlx_load_png(mlx->attributes[SO]);
	mlx->tex[WE] = mlx_load_png(mlx->attributes[WE]);
	mlx->tex[EA] = mlx_load_png(mlx->attributes[EA]);
	if (mlx->tex[NO] == NULL || mlx->tex[SO] == NULL || mlx->tex[WE] == NULL
		|| mlx->tex[EA] == NULL)
		return (true);
	return (false);
}

void	free_mlx(t_mlx *mlx)
{
	mlx_delete_image(mlx->win, mlx->img);
	mlx_delete_texture(mlx->tex[NO]);
	mlx_delete_texture(mlx->tex[SO]);
	mlx_delete_texture(mlx->tex[WE]);
	mlx_delete_texture(mlx->tex[EA]);
	mlx_terminate(mlx->win);
}

int	free_mlx_error(t_mlx *mlx)
{
	if (mlx->tex[NO])
		mlx_delete_texture(mlx->tex[NO]);
	if (mlx->tex[SO])
		mlx_delete_texture(mlx->tex[SO]);
	if (mlx->tex[WE])
		mlx_delete_texture(mlx->tex[WE]);
	if (mlx->tex[EA])
		mlx_delete_texture(mlx->tex[EA]);
	if (mlx->img)
		mlx_delete_image(mlx->win, mlx->img);
	if (mlx->win)
		mlx_terminate(mlx->win);
	return (you_made_the_l((char *)mlx_strerror(mlx_errno)));
}

int	make_it_visual(t_mlx *mlx, int vision_dir)
{
	mlx->win = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
	if (mlx->win == NULL)
		return (free_mlx_error(mlx));
	if (load_textures(mlx))
		return (free_mlx_error(mlx));
	mlx->img = mlx_new_image(mlx->win, WIDTH, HEIGHT);
	if (mlx->img == NULL)
		return (free_mlx_error(mlx));
	*getter_player_ang() = 360 - vision_dir;
	*getter_dir_x() = cos(RAD_1 * *getter_player_ang());
	*getter_dir_y() = sin(RAD_1 * *getter_player_ang());
	mlx_key_hook(mlx->win, keyboard, mlx);
	mlx_cursor_hook(mlx->win, mouse, mlx);
	mlx_loop_hook(mlx->win, render, mlx);
	mlx_set_mouse_pos(mlx->win, WIDTH_2, HEIGHT_2);
	mlx_set_cursor_mode(mlx->win, MLX_MOUSE_HIDDEN);
	mlx_image_to_window(mlx->win, mlx->img, 0, 0);
	mlx_loop(mlx->win);
	free_mlx(mlx);
	return (0);
}
