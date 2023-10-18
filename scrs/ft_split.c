/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adantas- <adantas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:04:26 by adantas-          #+#    #+#             */
/*   Updated: 2023/10/17 15:09:34 by adantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"

static void	clear_matrix(char **matrix)
{
	char	**temp;

	temp = matrix;
	while (temp)
	{
		free(*temp);
		temp++;
	}
	free(matrix);
}

static void	copy_word(const char *s, char *word, char c, size_t *index)
{
	size_t	position;

	position = 0;
	while (s[*index] != c && s[*index])
	{
		word[position] = s[*index];
		position++;
		(*index)++;
	}
	word[position] = '\0';
}

static size_t	get_word_size(const char *s, char c)
{
	size_t	size;

	size = 0;
	while (s[size] != c && s[size])
		size++;
	return (size);
}

static char	**allocate_strings(const char *s, char c, char **matrix, \
								size_t words)
{
	size_t	index;
	size_t	line;

	index = 0;
	line = 0;
	while (s[index] && line < words)
	{
		while (s[index] == c)
			index++;
		matrix[line] = malloc(get_word_size(s + index, c) + 1);
		if (matrix[line] == NULL)
		{
			clear_matrix(matrix);
			return (NULL);
		}
		copy_word(s, matrix[line], c, &index);
		line++;
	}
	matrix[line] = NULL;
	return (matrix);
}

char	**ft_split(const char *s, char c)
{
	char	**matrix;
	size_t	index;
	size_t	words;

	if (s == NULL)
		return (NULL);
	index = 0;
	words = 0;
	while (s[index])
	{
		while (s[index] == c)
			index++;
		if (s[index] != c && s[index])
			words++;
		while (s[index] != c && s[index])
			index++;
	}
	matrix = (char **)malloc(sizeof(char *) * (words + 1));
	if (matrix == NULL)
		return (NULL);
	return (allocate_strings(s, c, matrix, words));
}
