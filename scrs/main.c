/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adantas- <adantas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:31:56 by adantas-, r       #+#    #+#             */
/*   Updated: 2023/10/18 16:52:24 by adantas-         ###   ########.fr       */
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
	char	*inside;

	while (map != NULL)
	{
		inside = *map;
		while (*inside != 0)
		{
			if (*inside == 'N')
				return (90);
			else if (*inside == 'W')
				return (180);
			else if (*inside == 'S')
				return (270);
			else if (*inside == 'E')
				return (360);
			++inside;
		}
		++map;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	char	**map;
	char	*attributes[7];
	t_mlx	mlx;

	mlx = (t_mlx){0};
	if (error_checker(argc, argv))
		return (1);
	if (element_checker(argv[1], map))
		return (1);
	map = get_map(argv[1]);
	if (map == NULL)
		return (1);
	ft_memset(attributes, 0, sizeof(char *[7]));
	if (get_view_attributes(attributes, argv[1]))
	{
		ft_free_matrix((void **)map);
		return (1);
	}
	*getter_map() = map;
	mlx.attributes = attributes;
	make_it_visual(&mlx, where_to_look(map));
	ft_free_matrix((void **)map);
	free_local_matrix(attributes);
	return (0);
}
