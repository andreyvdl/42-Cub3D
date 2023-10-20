/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adantas-, rleite-s <adantas-@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:46:20 by adantas-, r       #+#    #+#             */
/*   Updated: 2023/10/20 20:25:29 by adantas-, r      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

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

void	ft_putendl_fd(int fd, char *str)
{
	if (fd < 0 || str == NULL)
		return ;
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
}
