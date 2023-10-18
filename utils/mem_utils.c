/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adantas- <adantas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:45:40 by adantas-, r       #+#    #+#             */
/*   Updated: 2023/10/18 13:28:53 by adantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

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
