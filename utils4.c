/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adantas- <adantas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:52:35 by adantas-          #+#    #+#             */
/*   Updated: 2023/10/17 13:52:46 by adantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"

void	free_local_matrix(char *matrix[])
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
		free(matrix[i++]);
}

static int	ft_isspace(char c)
{
	return (c == ' '
		|| c == '\f'
		|| c == '\n'
		|| c == '\r'
		|| c == '\t'
		|| c == '\v');
}

int	ft_atoi(const char *nptr)
{
	short int	signal;
	int			num;

	num = 0;
	while (ft_isspace(*nptr))
		nptr++;
	signal = (*nptr == '+' || ft_isdigit(*nptr)) - (*nptr == '-');
	nptr += (*nptr == '+' || *nptr == '-');
	while (ft_isdigit(*nptr))
		num = (num * 10) + (*nptr++ - '0');
	return (num * signal);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	index;

	index = -1;
	if (dest <= src)
		while (++index < n)
			((unsigned char *)dest)[index] = ((unsigned char *)src)[index];
	else
		while (n--)
			((unsigned char *)dest)[n] = ((unsigned char *)src)[n];
	return (dest);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	index;

	if (n == 0 || s == NULL)
		return (s);
	index = 0;
	while (index != n)
		((char *)s)[index++] = c;
	return (s);
}
