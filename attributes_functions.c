/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attributes_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adantas-, rleite-s <adantas-@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:22:01 by adantas-, r       #+#    #+#             */
/*   Updated: 2023/10/17 11:22:03 by adantas-, r      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



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
