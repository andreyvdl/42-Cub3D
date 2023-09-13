# include "cube.h"

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
	{
		puts("Make the L!");
		return (1);
	}
	file = argv[1];
	if (ft_strlen(file) < 5 || ft_strrchr(file, '.') == NULL
		|| ft_strcmp(ft_strrchr(file, '.'), ".cub"))
	{
		puts("Make the L! 2");
		return (1);
	}
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		puts("Make the L! 3");
		return (1);
	}
	close(fd);
	return (0);
}

void print_map(char **map)
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
	{
		puts("Make the L! 7");
		return (-1);
	}
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
	line = get_next_line(fd);
	match = 0;
	while (line && match != 6)
	{
		if (line[0] != '\n')
		{
			normalize_element(line);
			match = validate_element(line);
		}
		if (match == -1)
		{
			puts("Make the L! 6");
			free(line);
			close(fd);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd));
}

int	count_map_lines(char *file_path)
{
	char	*line;
	int		fd;
	int		map_lines;
	int		map_start;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		puts("Make the L! 5");
		return (-1);
	}
	map_lines = 0;
	line = get_next_line(fd);
	map_start = 0;
	while (line)
	{
		if (line[0] != '\n')
		{
			// split (matar \n antes do rolê)
			// if (split == NULL|| *split == NULL)
			// free(line);
			// puts ("Make the L 6");
			// return (-1);
			map_start++;
		}
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
		else
			free(line);
		if (line[0] != '\n' && map_start > 6)
			map[map_lines++] = line;
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
	new_line = malloc(new_size + 1);
	// Verificar erro
	ft_memmove(new_line, line, line_size);
	ft_memset(new_line + line_size, ' ', new_size - line_size);
	new_line[new_size] = 0;
	free(line);
	/* while (line_size < new_size)
		new_line[line_size++] = ' ';
	new_line[line_size] = 0; */
	return (new_line);
}

void	map_normalizer(char **map)
{
	size_t	max_line_size;
	size_t	index;
	char	**start;

	max_line_size = 0;
	start = map;
	while (*map)
	{
		index = 0;
		while (map[0][index])
		{
			if (map[0][index] == '\n' || map[0][index] == '\r')
				map[0][index] = 0;
			if (map[0][index] && index + 1 > max_line_size)
				max_line_size = index + 1;
			index++;
		}
		map++;
	}
	while (*start)
	{
		if (ft_strlen(*start) < max_line_size)
			*start = do_the_new_line(*start, max_line_size);
		start++;
	}
}

int	validate_map(char **map)
{
	size_t	line_index;
	size_t	column_index;

	// Valid size
	if (ft_matrixlen(map) < 3 || ft_strlen(map[0]) < 3)
	{
		puts("Make the L! 11");
		return (-1);
	}

	// Valid characters
	line_index = 0;
	while (map[line_index])
	{
		column_index = 0;
		while (map[line_index][column_index])
		{
			if (!ft_strchr("0 1NSWE", map[line_index][column_index]))
			{
				puts("Make the L 8!");
				return (-1);
			}
			column_index++;
		}
		line_index++;
	}
	// More than one player
	int	players = 0;

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
	{
		puts("Make the L 9!");
		return (-1);
	}
	// Map surrounded by walls
	line_index = 0;

	while (map[line_index])
	{
		column_index = 0;
		while (map[line_index][column_index])
		{
			if ((map[line_index][column_index] == '0' || ft_strchr("NSEW", map[line_index][column_index])) 
				&& (
					(line_index == 0 || !map[line_index + 1])// Linha zero ou linha final
					|| (column_index == 0)
					|| (!map[line_index][column_index + 1] || map[line_index][column_index + 1] == ' ') // Próximo é inválido
					|| (column_index > 0 && (!map[line_index][column_index - 1] || map[line_index][column_index - 1] == ' ')) // Anterior é inválido
				))
			{
				puts("Make the L! 10");
				return (-1);
			}
			column_index++;
		}
		line_index++;
	}
	return (0);
}

void	adjust_attributes(char *textures[])
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (*textures[i] == 'N' || *textures[i] == 'S'
			|| *textures[i] == 'W' || *textures[i] == 'E')
			ft_memmove(textures[i], textures[i] + 3,
				ft_strlen(textures[i] + 3) + 1);
		else if (*textures[i] == 'F' || *textures[i] == 'C')
			ft_memmove(textures[i], textures[i] + 2,
				ft_strlen(textures[i] + 2) + 1);
		++i;
	}
}

void	get_view_attributes(char *textures[], char *filename)
{
	const char	*elements[6] = {"NO ", "SO ", "WE ", "EA ", "F ", "C "};
	char		*line;
	int			fd;
	int			i;
	int			j;

	fd = open(filename, O_RDONLY);
	i = 0;
	while (i < 6)
	{
		line = get_next_line(fd);
		if (line[0] == '\n')
			free(line);
		else
		{
			normalize_element(line);
			j = 0;
			while (ft_strncmp(line, elements[j], ft_strlen(elements[j])) != 0)
				++j;
			textures[j] = line;
			++i;
		}
	}
	close(fd);
	adjust_attributes(textures);
}

int	main(int argc, char *argv[])
{
	int		map_lines;
	char	**map;
	char	*textures[6];

	if (error_checker(argc, argv))
		return (1);
	if (element_checker(argv[1], map))
		return (1);
	// Validar texturas das Coordenadas
	get_view_attributes(textures, argv[1]);
	map_lines = count_map_lines(argv[1]);
	if (map_lines < 0)
		return (2);
	map = do_the_map(argv[1], map_lines);
	if (!map)
		return (1);
	map_normalizer(map);
	validate_map(map);
	print_map(map);
	return (0);
}
