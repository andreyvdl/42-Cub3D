/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_invalid_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adantas-, rleite-s <adantas-@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:22:38 by adantas-, r       #+#    #+#             */
/*   Updated: 2023/10/20 20:24:14 by adantas-, r      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

int	has_invalid_character(char **map)
{
	size_t	line_index;
	size_t	column_index;

	line_index = 0;
	while (map[line_index])
	{
		column_index = 0;
		while (map[line_index][column_index])
		{
			if (!ft_strchr("0 1NSWE", map[line_index][column_index]))
				return (1);
			column_index++;
		}
		line_index++;
	}
	return (0);
}

int	has_invalid_number_of_players(char **map)
{
	size_t	line_index;
	size_t	column_index;
	int		players;

	players = 0;
	line_index = 0;
	while (map[line_index])
	{
		column_index = 0;
		while (map[line_index][column_index])
		{
			if (ft_strchr("NSWE", map[line_index][column_index]))
				players++;
			column_index++;
		}
		if (players > 1)
			break ;
		line_index++;
	}
	if (players != 1)
		return (1);
	return (0);
}

int	has_invalid_walls(char **map)
{
	size_t	line_index;
	size_t	column_index;

	line_index = 0;
	while (map[line_index])
	{
		column_index = 0;
		while (map[line_index][column_index])
		{
			if ((map[line_index][column_index] == '0'
				|| ft_strchr("NSEW", map[line_index][column_index])) \
			&& ((line_index == 0 || !map[line_index + 1])
				|| (column_index == 0)
				|| (!map[line_index][column_index + 1]
				|| map[line_index][column_index + 1] == ' ')
				|| (column_index > 0 && (!map[line_index][column_index - 1]
				|| map[line_index][column_index - 1] == ' '))
			))
				return (1);
			column_index++;
		}
		line_index++;
	}
	return (0);
}

int	has_invalid_color(char **lines)
{
	char	**split;

	if (find_and_count(*lines, ',') != 2)
		return (-1);
	split = ft_split(*lines, ',');
	if (ft_matrixlen(split) != 3)
	{
		ft_free_matrix((void **)split);
		return (-1);
	}
	else if (has_invalid_number(split[0]) || has_invalid_number(split[1]) || \
	has_invalid_number(split[2]))
	{
		ft_free_matrix((void **)split);
		return (-1);
	}
	ft_free_matrix((void **)split);
	return (0);
}

int	has_invalid_number(char *str)
{
	size_t	i;
	size_t	j;
	int		n;

	j = 0;
	while (str[j] == '0')
		++j;
	i = j;
	while (ft_isdigit(str[i]))
		++i;
	if (i - j > 3 || str[i] != '\0')
		return (-1);
	n = ft_atoi(str);
	if (n > 255)
		return (-1);
	return (0);
}
