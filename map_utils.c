/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adantas- <adantas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:30:57 by adantas-, r       #+#    #+#             */
/*   Updated: 2023/10/17 14:23:51 by adantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"

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

int	is_only_spaces(char *line)
{
	while (line && *line)
	{
		if (*line != ' ')
			break ;
		line++;
	}
	if (line && (*line == '\n' || *line == '\r'))
		*line = 0;
	if (line && *line == 0)
		return (1);
	return (0);
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
