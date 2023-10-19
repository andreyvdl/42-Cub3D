/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_globals2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adantas- <adantas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:10:23 by adantas-          #+#    #+#             */
/*   Updated: 2023/10/18 15:11:19 by adantas-         ###   ########.fr       */
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
