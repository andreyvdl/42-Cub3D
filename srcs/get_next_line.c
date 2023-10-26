/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adantas-, rleite-s <adantas-@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:55:53 by rleite-s          #+#    #+#             */
/*   Updated: 2023/10/26 11:30:51 by adantas-, r      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

ssize_t	where_line_feed(char *buffer)
{
	ssize_t	index;

	index = 0;
	while (buffer[index] != '\n' && buffer[index])
		index++;
	return (index);
}

short int	check_buffer(char **buffer, char **line, char *aux)
{
	ssize_t	index;

	if (*buffer)
	{
		index = where_line_feed(*buffer);
		if (!(*buffer)[index])
		{
			*line = *buffer;
			*buffer = NULL;
		}
		else
		{
			aux = *buffer;
			*line = ft_substr(*buffer, 0, index + 1);
			if ((*buffer)[index + 1])
				*buffer = ft_strdup(*buffer + index + 1);
			else
				*buffer = NULL;
			free(aux);
			return (0);
		}
	}
	return (1);
}

short int	check_readed(ssize_t *readed, int fd, char **text, char **buffer)
{
	free(*text);
	*text = (char *)malloc(BUFFER_SIZE + *readed + 1);
	*readed = read(fd, *text, BUFFER_SIZE + *readed);
	if (*readed < 0)
	{
		free(*buffer);
		*buffer = NULL;
		return (1);
	}
	return (0);
}

char	*get_next_line_1(int fd, char **buffer)
{
	char		*text;
	char		*line;
	ssize_t		readed;

	line = NULL;
	if (check_buffer(buffer, &line, NULL))
	{
		text = (char *)malloc(BUFFER_SIZE + 1);
		readed = read(fd, text, BUFFER_SIZE);
		while (readed > 0)
		{
			text[readed] = 0;
			*buffer = ft_strjoin(line, text);
			free(line);
			if (check_buffer(buffer, &line, NULL) == 0)
				break ;
			if (check_readed(&readed, fd, &text, buffer))
				return (*buffer);
		}
		free(text);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	return (get_next_line_1(fd, &buffer));
}
