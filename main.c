# include "cube.h"

int	error_checker(int argc, char *argv[])
{
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
		printf("%s", map[i]);
	if (!ft_strrchr(map[i - 1], '\n'))
		puts("");
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
	map_lines = coun_map_lines(argv[1]);
	if (map_lines < 0)
		return (2);
	map = do_the_map(argv[1], map_lines);
	if (!map)
		return (1);
	print_map(map);
	return (0);
}
