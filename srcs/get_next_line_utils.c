/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adantas-, rleite-s <adantas-@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 20:13:48 by rleite-s          #+#    #+#             */
/*   Updated: 2023/10/26 11:29:58 by adantas-, r      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	s_len;

	s_len = ft_strlen(s);
	if (!s || !*s || !(start < s_len && len > 0))
		return (NULL);
	if (len >= s_len)
		sub = (char *)malloc((s_len - start + 1) * sizeof(char));
	else
		sub = (char *)malloc(len + 1);
	start = 0;
	while (len-- > 0 && s[start])
	{
		sub[start] = s[start];
		start++;
	}
	sub[start] = 0;
	return (sub);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*join;
	char	*index;

	if (!s1 && !s2)
		return (NULL);
	join = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (join == NULL)
		return (NULL);
	index = join;
	while (s1 && *s1)
		*index++ = *s1++;
	while (s2 && *s2)
		*index++ = *s2++;
	*index = '\0';
	return (join);
}
