/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_start_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adantas- <adantas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:59:56 by adantas-          #+#    #+#             */
/*   Updated: 2023/10/23 12:00:16 by adantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

bool	load_textures(t_mlx *mlx)
{
	mlx->tex[NO] = mlx_load_png(mlx->elements[NO]);
	mlx->tex[SO] = mlx_load_png(mlx->elements[SO]);
	mlx->tex[WE] = mlx_load_png(mlx->elements[WE]);
	mlx->tex[EA] = mlx_load_png(mlx->elements[EA]);
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

int	free_mlx_error(t_mlx *mlx, mlx_errno_t mlx_error)
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
	return (you_made_the_l((char *)mlx_strerror(mlx_error)));
}

int	make_it_visual(t_mlx *mlx, int vision_dir)
{
	mlx->win = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
	if (mlx->win == NULL)
		return (free_mlx_error(mlx, MLX_WINFAIL));
	if (load_textures(mlx))
		return (free_mlx_error(mlx, MLX_INVPNG));
	mlx->img = mlx_new_image(mlx->win, WIDTH, HEIGHT);
	if (mlx->img == NULL)
		return (free_mlx_error(mlx, MLX_MEMFAIL));
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
