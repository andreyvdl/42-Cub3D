/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adantas- <adantas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:56:01 by adantas-          #+#    #+#             */
/*   Updated: 2023/10/24 15:16:22 by adantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void	movement_keys(t_mlx *mlx)
{
	if (mlx_is_key_down(mlx->win, MLX_KEY_W) \
	|| mlx_is_key_down(mlx->win, MLX_KEY_UP))
		change_pos(*getter_dir_x(), *getter_dir_y());
	else if (mlx_is_key_down(mlx->win, MLX_KEY_S) \
	|| mlx_is_key_down(mlx->win, MLX_KEY_DOWN))
		change_pos(-*getter_dir_x(), -*getter_dir_y());
	if (mlx_is_key_down(mlx->win, MLX_KEY_D))
		change_pos(cos(RAD_1 * (*getter_player_ang() + 90)),
			sin(RAD_1 * (*getter_player_ang() + 90)));
	else if (mlx_is_key_down(mlx->win, MLX_KEY_A))
		change_pos(-cos(RAD_1 * (*getter_player_ang() + 90)),
			-sin(RAD_1 * (*getter_player_ang() + 90)));
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
	else if (mlx_is_key_down(mlx->win, MLX_KEY_RIGHT))
		*getter_player_ang() = (*getter_player_ang() + ROT_ANG) % 360;
	*getter_dir_x() = cos(*getter_player_ang() * RAD_1);
	*getter_dir_y() = sin(*getter_player_ang() * RAD_1);
	movement_keys(mlx);
}
