
#include "cube.h"

size_t	ft_strlen(char *s)
{
	size_t	len;

	len = 0;
	if (s == NULL)
		return (len);
	while (s[len] != '\0')
		len++;
	return (len);
}

char	*ft_strdup(char *s)
{
	size_t	len;
	char	*dup;

	len = 0;
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

char	*ft_strchr(char *s, int c)
{
	size_t	index;

	index = 0;
	while (s[index] != '\0')
	{
		if (s[index] == c)
			return (s + index);
		++index;
	}
	if (*s == c)
		return (s);
	return (NULL);
}

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	int		difference;
	size_t	index;

	if (n == 0)
		return (0);
	while (n)
	{
		difference = (int)*s1++ - (int)*s2++;
		if (difference != 0)
			return (difference);
		--n;
	}
	return (difference);
}

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
