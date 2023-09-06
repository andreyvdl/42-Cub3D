
#include "cube.h"

size_t	ft_strlen(const char *s)
{
	size_t	len = 0;

	if (s == NULL)
		return (len);
	while (s[len] != '\0')
		len++;
	return (len);
}

char	*ft_strdup(const char *s)
{
	size_t	len = 0;
	char	*dup;

	if (!s || s[0] == '\0')
		return (NULL);
	while (s[len])
		len++;
	dup = malloc (++len);
	if (!dup)
		return (NULL);
	while (len--)
		dup[len] = s[len];
	return (dup);
}

char	*ft_strrchr(char *s, int c)
{
	size_t	index;

	index = ft_strlen(s);
	while (index)
	{
		if (s[index] == c)
			return (s + index);
		--index;
	}
	if (*s == c)
		return (s);
	return (NULL);
}

int	ft_strcmp(char *s1, char *s2)
{
	int		difference;

	while (*s1 != '\0' && *s2 != '\0')
	{
		difference = (int)*s1++ - (int)*s2++;
		if (difference != 0)
			return (difference);
	}
	difference = (int)*s1 - (int)*s2;
	return (difference);
}