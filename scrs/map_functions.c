/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adantas- <adantas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:16:33 by adantas-, r       #+#    #+#             */
/*   Updated: 2023/10/18 16:53:05 by adantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

int	count_map_lines(int fd, int map_lines, int itens_ignore, int map_start)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (you_made_the_l("Make the L! 5"));
	while (line && map_lines >= 0)
	{
		if (line[0] != '\n' && itens_ignore < 6)
			itens_ignore++;
		else if (line[0] != '\n' && itens_ignore == 6)
		{
			if (map_start == 2)
				map_lines = (you_made_the_l("Abyss, mother fucker!")) - 1;
			if (is_only_spaces(line))
				map_lines = (you_made_the_l("Line with only spaces.")) - 1;
			map_lines++;
		}
		else if (line[0] == '\n' && itens_ignore == 6 && map_lines > 0)
			map_start = 2;
		free(line);
		if (map_lines >= 0)
			line = get_next_line(fd);
	}
	close(fd);
	return (map_lines);
}

char	**do_the_map(int fd, int map_lines)
{
	int		map_start;
	char	*line;
	char	**map;

	line = get_next_line(fd);
	if (!line)
		return (NULL);
	map = malloc((map_lines + 1) * sizeof(char *));
	if (!map)
		return (NULL);
	map_start = 0;
	map_lines = 0;
	while (line)
	{
		if (line[0] != '\n')
			map_start++;
		if (line[0] != '\n' && map_start > 6)
			map[map_lines++] = line;
		else if (line[0] == '\n' || map_start <= 6)
			free(line);
		line = get_next_line(fd);
	}
	map[map_lines] = line;
	close(fd);
	return (map);
}

int	map_normalizer(char **map)
{
	size_t	max_line_size;
	size_t	index;
	char	**start;

	max_line_size = 0;
	start = map;
	remove_newline_and_carriage(map);
	while (*map)
	{
		index = ft_strlen(*map++);
		if (index > max_line_size)
			max_line_size = index;
	}
	map = start;
	while (*start)
	{
		*start = do_the_new_line(*start, max_line_size);
		if (!*start++)
		{
			free_local_matrix(start);
			ft_free_matrix((void **)map);
			return (-1);
		}
	}
	return (0);
}

int	validate_map(char **map)
{
	size_t	line_index;
	size_t	column_index;

	if (ft_matrixlen(map) < 3 || ft_strlen(map[0]) < 3)
		return (you_made_the_l("Make the L! 11"));
	if (has_invalid_character(map))
		return (you_made_the_l("Make the L! 8"));
	if (has_invalid_number_of_players(map))
		return (you_made_the_l("Make the L! 9"));
	if (has_invalid_walls(map))
		return (you_made_the_l("Make the L! 10"));
	return (0);
}

char	**get_map(char *filename)
{
	int		map_lines;
	char	**map;

	map_lines = count_map_lines(open(filename, O_RDONLY), 0, 0, 0);
	if (map_lines < 0)
		return (NULL);
	map = do_the_map(open(filename, O_RDONLY), map_lines);
	if (!map)
		return (NULL);
	if (map_normalizer(map))
		return (NULL);
	if (validate_map(map))
	{
		ft_free_matrix((void **)map);
		map = NULL;
	}
	return (map);
}