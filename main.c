# include "cube.h"

int	you_made_the_l(char *str)
{
	puts("Error\n");
	puts(str);
	return (-1);
}

int	all_chars_is_in_set(char *arg, char *set)
{
	while (*arg && ft_strchr(set, *arg))
	{
		arg++;
	}
	if (*arg == 0)
		return (1);
	return (0);
}

int	error_checker(int argc, char *argv[])
{
	char	*file;
	int		fd;

	if (argc != 2)
		return (you_made_the_l("Make the L!"));
	file = argv[1];
	if (ft_strlen(file) < 5 || ft_strrchr(file, '.') == NULL \
	|| ft_strcmp(ft_strrchr(file, '.'), ".cub"))
		return (you_made_the_l("Make the L! 2"));
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (you_made_the_l("Make the L! 3"));
	close(fd);
	return (0);
}

void	print_map(char **map)
{
	int	i;
	for (i = 0; map[i]; i++)
		printf("'%s'\n", map[i]);
	if (!ft_strrchr(map[i - 1], '\n'))
		puts("");
}

int	invalid_number(char *str)
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

size_t	find_and_count(char *str, char c)
{
	size_t	n;

	if (str == NULL)
		return (0);
	n = 0;
	while (*str != '\0')
		if (*str++ == c)
			++n;
	return (n);
}

int	colors_invalid(char **lines)
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
	else if (invalid_number(split[0]) || invalid_number(split[1]) || \
	invalid_number(split[2]))
	{
		ft_free_matrix((void **)split);
		return (-1);
	}
	ft_free_matrix((void **)split);
	return (0);
}

int	validate_element(char *line)
{
	char		**splited;
	static char	*matched[6] = {NULL, NULL, NULL, NULL, NULL, NULL};
	const char	*elements[6] = {"NO ", "SO ", "WE ", "EA ", "F ", "C "};
	static int	matches;
	int			i;

	i = 0;
	while (i < 6 && ft_strncmp(elements[i], line, ft_strlen(elements[i])) != 0)
		++i;
	if (i == 6)
		return (-1);
	if (matched[i] != NULL)
		return (you_made_the_l("Make the L! 7"));
	matched[i] = (char *)elements[i];
	matches++;
	splited = ft_split(line, ' ');
	if (splited[1] == NULL || splited[2] != NULL
		|| (i >= 4 && colors_invalid(splited + 1)))
		matches = -1;
	ft_free_matrix((void **)splited);
	return (matches);
}

void	normalize_element(char *start)
{
	char	*end;

	end = start;
	while (*end && *end == ' ')
		end++;
	if (start != end)
		ft_memmove(start, end, ft_strlen(end) + 1);
	while (*start)
	{
		if (*start == ' ')
		{
			end = start + 1;
			while (*end && *end == ' ')
				end++;
			if (start + 1 != end)
				ft_memmove(start + 1, end, ft_strlen(end) + 1);
		}
		if ((*start == '\n' || *start == '\r') && start[1] == '\0')
			*start = 0;
		if (*start)
			start++;
	}
}

int	element_checker(char *filename, char **map)
{
	int		fd;
	char	*line;
	int		match;

	fd = open(filename, O_RDONLY);
	match = 0;
	while (match != 6)
	{
		line = get_next_line(fd);
		if (line[0] != '\n')
		{
			normalize_element(line);
			match = validate_element(line);
		}
		free(line);
		if (match == -1)
			break ;
	}
	close(fd);
	if (match == -1)
		return (you_made_the_l("Make the L! 6"));
	return (0);
}

int	count_map_lines(char *file_path)
{
	char	*line;
	int		fd;
	int		map_lines;
	int		map_start;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (you_made_the_l("Make the L! 5"));
	map_lines = 0;
	line = get_next_line(fd);
	map_start = 0;
	while (line)
	{
		if (line[0] != '\n')
			map_start++;
		if (line[0] != '\n' && map_start > 6)
			map_lines++;
		// Casos faltantes: map doesn't exists, wrong map (abyss or too much \n)
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (map_lines);
}

char	**do_the_map(char *file_path, int map_lines)
{
	int		fd;
	int		map_start;
	char	*line;
	char	**map;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	map = malloc((map_lines + 1) * sizeof(char *));
	if (!map)
		return (NULL);
	map_start = 0;
	line = get_next_line(fd);
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

char	*do_the_new_line(char *line, size_t new_size)
{
	size_t	line_size;
	char	*new_line;

	line_size = ft_strlen(line);
	if (line_size == new_size)
		return (line);
	new_line = malloc(new_size + 1);
	if (!new_line)
	{
		free(line);
		return (NULL);
	}
	ft_memmove(new_line, line, line_size);
	ft_memset(new_line + line_size, ' ', new_size - line_size);
	new_line[new_size] = 0;
	free(line);
	return (new_line);
}

void	remove_newline_and_carriage(char **map)
{
	size_t	i;

	while (*map)
	{
		i = 0;
		while ((*map)[i])
		{
			if ((*map)[i] == '\n' || (*map)[i] == '\r')
				(*map)[i] = 0;
			++i;
		}
		++map;
	}
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
	int	players;

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
			if ((map[line_index][column_index] == '0' || ft_strchr("NSEW", map[line_index][column_index])) \
			&& ((line_index == 0 || !map[line_index + 1])
				|| (column_index == 0)
				|| (!map[line_index][column_index + 1] || map[line_index][column_index + 1] == ' ')
				|| (column_index > 0 && (!map[line_index][column_index - 1] || map[line_index][column_index - 1] == ' '))
			))
				return (1);
			column_index++;
		}
		line_index++;
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

void	adjust_attributes(char *textures[])
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (*textures[i] == 'N' || *textures[i] == 'S' \
		|| *textures[i] == 'W' || *textures[i] == 'E')
			ft_memmove(textures[i], textures[i] + 3,
				ft_strlen(textures[i] + 3) + 1);
		else if (*textures[i] == 'F' || *textures[i] == 'C')
			ft_memmove(textures[i], textures[i] + 2,
				ft_strlen(textures[i] + 2) + 1);
		++i;
	}
}

int	got_new_attribute(char *textures[], char **elements, char *new)
{
	int	i;

	i = 0;
	if (!new[0])
	{
		free(new);
		return (0);
	}
	while (ft_strncmp(new, elements[i], ft_strlen(elements[i])) != 0)
		++i;
	textures[i] = &*new;
	return (1);
}

int	get_view_attributes(char *textures[], char *filename)
{
	const char	*elements[6] = {"NO ", "SO ", "WE ", "EA ", "F ", "C "};
	char		*line;
	int			fd;
	int			i;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (-1);
	i = 0;
	while (i < 6)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			close(fd);
			free_local_matrix(textures);
			return (-1);
		}
		normalize_element(line);
		if (got_new_attribute(textures, (char **)elements, line))
			++i;
	}
	close(fd);
	adjust_attributes(textures);
	return (0);
}

char	**get_map(char *filename)
{
	int		map_lines;
	char	**map;

	map_lines = count_map_lines(filename);
	if (map_lines < 0)
		return (NULL);
	map = do_the_map(filename, map_lines);
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

int	main(int argc, char *argv[])
{
	char	**map;
	char	*textures[7];

	if (error_checker(argc, argv))
		return (1);
	if (element_checker(argv[1], map))
		return (1);
	map = get_map(argv[1]);
	if (map == NULL)
		return (1);
	ft_memset(textures, 0, sizeof(char *[7]));
	if (get_view_attributes(textures, argv[1]))
	{
		ft_free_matrix((void **)map);
		return (1);
	}
	print_map(map);
	ft_free_matrix((void **)map);
	free_local_matrix(textures);
	return (0);
}
