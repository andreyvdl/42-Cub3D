/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleite-s <rleite-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:31:56 by adantas-, r       #+#    #+#             */
/*   Updated: 2023/10/19 16:41:27 by rleite-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

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

int	where_to_look(char **map)
{
	int	direction;

	direction = 360;
	if (map[(int)*getter_player_y() / SIZE] \
			[(int)*getter_player_x() / SIZE] == 'N')
		direction = 90;
	else if (map[(int)*getter_player_y() / SIZE] \
			[(int)*getter_player_x() / SIZE] == 'S')
		direction = 270;
	else if (map[(int)*getter_player_y() / SIZE] \
			[(int)*getter_player_x() / SIZE] == 'W')
		direction = 180;
	return (direction);
}

void	set_player_pos(void)
{
	const char	**map = (const char **)(*getter_map());
	size_t		i;
	size_t		j;

	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != 0)
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' \
				|| map[i][j] == 'W')
			{
				*getter_player_x() = j * SIZE;
				*getter_player_y() = i * SIZE;
				return ;
			}
			++j;
		}
		++i;
	}
}

void	set_colors_and_get_player_pos(t_mlx *mlx)
{
	char	**split;

	split = ft_split(mlx->elements[4], ',');
	if (split == NULL)
	{
		ft_free_matrix(*getter_map());
		free_local_matrix(mlx->elements);
		you_made_the_l("Malloc error. You computer is burning.");
		exit(2);
	}
	mlx->floor = (uint32_t)(ft_atoi(split[R]) << 24 | ft_atoi(split[G]) << 16 \
							| ft_atoi(split[B]) << 8 | 255);
	ft_free_matrix((void **)split);
	split = ft_split(mlx->elements[5], ',');
	if (split == NULL)
	{
		ft_free_matrix(*getter_map());
		free_local_matrix(mlx->elements);
		you_made_the_l("Malloc error. You computer is burning.");
		exit(2);
	}
	mlx->ceil = (uint32_t)(ft_atoi(split[R]) << 24 | ft_atoi(split[G]) << 16 \
							| ft_atoi(split[B]) << 8 | 255);
	set_player_pos();
}

int	main(int argc, char *argv[])
{
	char	**map;
	char	*elements[7];
	t_mlx	mlx;

	mlx = (t_mlx){0};
	if (error_checker(argc, argv))
		return (1);
	if (element_checker(argv[1]))
		return (1);
	map = get_map(argv[1]);
	if (map == NULL)
		return (1);
	ft_memset(elements, 0, sizeof(char *[7]));
	if (get_view_elements(elements, argv[1]))
	{
		ft_free_matrix((void **)map);
		return (1);
	}
	*getter_map() = map;
	mlx.elements = elements;
	set_colors_and_get_player_pos(&mlx);
	make_it_visual(&mlx, where_to_look(map));
	ft_free_matrix((void **)map);
	free_local_matrix(elements);
	return (0);
}
