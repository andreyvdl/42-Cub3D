/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_globals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adantas-, rleite-s <adantas-@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:10:23 by adantas-          #+#    #+#             */
/*   Updated: 2023/10/20 20:24:55 by adantas-, r      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

char	***getter_map(void)
{
	static char	**map;

	return (&map);
}

mlx_texture_t	**getter_tex(void)
{
	static mlx_texture_t	*tex;

	return (&tex);
}
