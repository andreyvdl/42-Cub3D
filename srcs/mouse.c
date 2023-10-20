/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adantas-, rleite-s <adantas-@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:58:54 by adantas-          #+#    #+#             */
/*   Updated: 2023/10/20 20:24:35 by adantas-, r      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void	toggle_mouse(t_mlx *mlx)
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
	mlx_set_mouse_pos(mlx->win, WIDTH_2, HEIGHT_2);
}

void	mouse(double x_pos, double y_pos, void *var)
{
	t_mlx	*mlx;

	(void)y_pos;
	mlx = (t_mlx *)var;
	if (mlx->m_cntl == true)
		return ;
	if (x_pos < WIDTH_2)
		*getter_player_ang() -= ROT_ANG * 0.5;
	else if (x_pos > WIDTH_2)
		*getter_player_ang() += ROT_ANG * 0.5;
	if (*getter_player_ang() < 0)
		*getter_player_ang() += 360;
	if (*getter_player_ang() > 360)
		*getter_player_ang() -= 360;
	*getter_dir_x() = cos(RAD_1 * *getter_player_ang());
	*getter_dir_y() = sin(RAD_1 * *getter_player_ang());
	mlx_set_mouse_pos(mlx->win, WIDTH_2, HEIGHT_2);
}
