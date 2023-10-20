/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adantas-, rleite-s <adantas-@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:55:53 by rleite-s          #+#    #+#             */
/*   Updated: 2023/10/20 20:24:10 by adantas-, r      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

int	has_line_feed(t_text *text)
{
	while (text)
	{
		if (text->letter == '\n')
			return (1);
		text = text->next;
	}
	return (0);
}

size_t	get_line_len(t_text *text)
{
	size_t	len;

	len = 0;
	while (text)
	{
		if (text->letter == '\n')
			return (len + 1);
		text = text->next;
		len++;
	}
	return (len);
}

int	read_text(int fd, t_text **text)
{
	char	*line;
	size_t	i;
	ssize_t	returned;

	line = malloc(BUFFER_SIZE);
	if (!line)
		return (-1);
	while (!has_line_feed(*text))
	{
		returned = read(fd, line, BUFFER_SIZE);
		if (returned <= 0)
			break ;
		i = 0;
		while (i < returned)
		{
			if (insert_into_list(text, line[i++]))
			{
				free (line);
				return (-1);
			}
		}
	}
	free(line);
	return (returned);
}

char	*get_line(t_text **text)
{
	char	*line;
	size_t	line_len;
	size_t	i;

	if (!text || !*text)
		return (NULL);
	line_len = get_line_len(text);
	line = malloc(line_len + 1);
	if (!line)
	{
		free_list(text);
		return (NULL);
	}
	i = 0;
	while (i < line_len)
	{
		line[i++] = (*text)->letter;
		free_node(text);
	}
	line[i] = 0;
	return (line);
}

char	*get_next_line(int fd)
{
	static t_text	*text;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free_list(&text);
		return (NULL);
	}
	if (read_text(fd, &text) == -1)
		free_list(&text);
	return (get_line(&text));
}
