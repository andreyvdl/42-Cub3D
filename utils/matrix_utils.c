/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adantas-, rleite-s <adantas-@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:51:46 by adantas-          #+#    #+#             */
/*   Updated: 2023/10/20 20:25:12 by adantas-, r      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

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

void	free_local_matrix(char *matrix[])
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
		free(matrix[i++]);
}
