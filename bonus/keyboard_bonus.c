/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adantas- <adantas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:53:23 by adantas-          #+#    #+#             */
/*   Updated: 2023/10/23 11:56:19 by adantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void	movement_keys(t_mlx *mlx)
{
	if (mlx_is_key_down(mlx->win, MLX_KEY_W))
		change_pos(*getter_dir_x(), *getter_dir_y());
	if (mlx_is_key_down(mlx->win, MLX_KEY_S))
		change_pos(-*getter_dir_x(), -*getter_dir_y());
	if (mlx_is_key_down(mlx->win, MLX_KEY_D))
		change_pos(cos(RAD_1 * (*getter_player_ang() + 90)) * 2,
			sin(RAD_1 * (*getter_player_ang() + 90)) * 2);
	if (mlx_is_key_down(mlx->win, MLX_KEY_A))
		change_pos(-cos(RAD_1 * (*getter_player_ang() + 90)) * 2,
			-sin(RAD_1 * (*getter_player_ang() + 90)) * 2);
}

void	keyboard(mlx_key_data_t data, void *var)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)var;
	if (data.key == MLX_KEY_ESCAPE)
		mlx_close_window(mlx->win);
	if (mlx_is_key_down(mlx->win, MLX_KEY_LEFT))
	{
		*getter_player_ang() -= ROT_ANG;
		if (*getter_player_ang() < 0)
			*getter_player_ang() = 360 + *getter_player_ang();
	}
	if (mlx_is_key_down(mlx->win, MLX_KEY_RIGHT))
		*getter_player_ang() = (*getter_player_ang() + ROT_ANG) % 360;
	*getter_dir_x() = cos(*getter_player_ang() * RAD_1);
	*getter_dir_y() = sin(*getter_player_ang() * RAD_1);
	if (data.key == MLX_KEY_L && data.action == MLX_RELEASE)
		toggle_mouse(mlx);
	else
		movement_keys(mlx);
}
