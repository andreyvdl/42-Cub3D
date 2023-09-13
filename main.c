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
	// Validar se o arquivo.cub abre
	if (argc != 2)
	{
		puts("Make the L!");
		return (1);
	}
	if (ft_strlen(argv[1]) < 5)
	{
		puts("Make the L! 2");
		return (1);
	}
	else if (ft_strrchr(argv[1], '.') == NULL)
	{
		puts("Make the L! 3");
		return (1);
	}
	else if (ft_strcmp(ft_strrchr(argv[1], '.'), ".cub"))
	{
		puts("Make the L! 4");
		return (1);
	}
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
	n = ft_atoi(str); // precisa adicionar a atoi
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
	// Validar F e C
	// Se não houver something that is comma e número, quita (set?) (último número nunca terá vírgula)
	// Número entre 0 e 255 (montado conforme atoi) [Checar se cabe no range 0-255, vide minishell]
	// Salvar nada
	// possibilidades: [123,123,123] | [123,123,123,blblbl] | [123,123,123bla]
	// [123bla,123,123] | [123,123bla,123]
	if (find_and_count(*lines, ' ') != 2)
		return (-1);
	// split aqui por virgulas
	// resto está só pre codado
	char	**split = ft_split(*lines, ',');
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
	char		*elements[6] = {"NO ", "SO ", "WE ", "EA ", "F ", "C "};
	static int	matches;
	int			i;

	i = 0;
	while (i < 6 && ft_strncmp(elements[i], line, ft_strlen(elements[i])) != 0)
		++i;
	if (i == 6)
		return (-1);
	if (matched[i] != NULL)
	{
		puts("Make the L! 8");
		return (-1);
	}
	matched[i] = elements[i];
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
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

int	coun_map_lines(char *file_path)
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

int	main(int argc, char *argv[])
{
	int		map_lines;
	char	**map;

	if (error_checker(argc, argv))
		return (1);
	if (element_checker(argv[1], map))
		return (1);
	map_lines = coun_map_lines(argv[1]);
	if (map_lines < 0)
		return (2);
	map = do_the_map(argv[1], map_lines);
	if (!map)
		return (1);
	print_map(map);
	return (0);
}
