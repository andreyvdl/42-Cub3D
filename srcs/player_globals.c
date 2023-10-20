/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_globals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adantas-, rleite-s <adantas-@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:49:56 by adantas-, r       #+#    #+#             */
/*   Updated: 2023/10/20 20:24:39 by adantas-, r      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

double	*getter_player_x(void)
{
	static double	player_x;

	return (&player_x);
}

double	*getter_player_y(void)
{
	static double	player_y;

	return (&player_y);
}

int	*getter_player_ang(void)
{
	static int	player_angle;

	return (&player_angle);
}

double	*getter_dir_x(void)
{
	static double	dir_x;

	return (&dir_x);
}

double	*getter_dir_y(void)
{
	static double	dir_y;

	return (&dir_y);
}
