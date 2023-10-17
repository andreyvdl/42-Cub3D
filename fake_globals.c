/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_globals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adantas-, rleite-s <adantas-@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:49:56 by adantas-, r       #+#    #+#             */
/*   Updated: 2023/10/17 12:09:25 by adantas-, r      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_test.h"

double	*g_player_x(void)
{
	static double	player_x;

	return (&player_x);
}

double	*g_player_y(void)
{
	static double	player_y;

	return (&player_y);
}

int	*g_player_angle(void)
{
	static int	player_angle;
	
	return (&player_angle);
}

double	*g_dir_x(void)
{
	static double	dir_x;
	
	return (&dir_x);
}

double	*g_dir_y(void)
{
	static double	dir_y;

	return (&dir_y);
}