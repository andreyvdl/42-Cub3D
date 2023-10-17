/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adantas- <adantas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:51:46 by adantas-          #+#    #+#             */
/*   Updated: 2023/10/17 13:52:16 by adantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"

char	*ft_strtrim(char *s1, char *set)
{
	size_t	start;
	size_t	end;
	size_t	i;
	char	*trimmed;

	if (s1 == NULL)
		return (NULL);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]) != NULL)
		++start;
	end = ft_strlen(s1) - 1;
	while (end > start && ft_strchr(set, s1[end]) != NULL)
		--end;
	trimmed = malloc(end - start + 1);
	i = 0;
	while (start <= end)
		trimmed[i++] = s1[start++];
	trimmed[i] = 0;
	return (trimmed);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	difference;

	while (*s1 != '\0' && *s2 != '\0')
	{
		difference = (int)*s1++ - (int)*s2++;
		if (difference != 0)
			return (difference);
	}
	difference = (int)*s1 - (int)*s2;
	return (difference);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

size_t	ft_matrixlen(char **matrix)
{
	size_t	size;

	if (matrix == NULL)
		return (0);
	size = 0;
	while (matrix[size] != NULL)
		++size;
	return (size);
}

void	ft_free_matrix(void **matrix)
{
	char	**temp;

	if (matrix)
	{
		temp = (char **)matrix;
		while (*temp)
			free(*temp++);
		free(matrix);
	}
}
