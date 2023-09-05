# include "cube.h"

size_t    ft_strlen(char *s)
{
    size_t    len = 0;

    if (s == NULL)
        return (len);
    while (s[len] != '\0')
        len++;
    return (len);
}

char    *ft_strdup(char *s)
{
    size_t    len = 0;
    char    *dup;

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

char	*ft_realloc(char *s1, char *s2)
{
	char	*new;
	size_t	index1 = 0;
	size_t	index2 = 0;
	size_t	index_new = 0;

	if (s1 == NULL && s2 == NULL)
	{
		return (NULL);
	}
	new = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new)
	{
		return (NULL);
	}
	while (s1 != NULL && s1[index1] != '\0')
	{
		new[index_new] = s1[index1];
		index_new++;
		index1++;
	}
	free(s1);
	while (s2 != NULL && s2[index2] != '\0')
	{
		new[index_new] = s2[index2];
		index_new++;
		index2++;
	}
	new[index_new] = 0;
	return (new);
}

char    *get_next_line(int fd)
{
    static char    *rest;
    char        *line;
    char        *aux;
    int            i = 0;
    long        bytes_read = 1;

    if (rest != NULL)
    {
        while (rest[i] != '\n' && rest[i] != '\0')
            i++;
        if (rest[i] == '\n')
        {
            char    bkp = rest[i + 1]; 
            rest[i + 1] = '\0';
            line = ft_strdup(rest);
            if (!line)
            {
                free(rest);
                rest = NULL;
                return (NULL);
            }
            rest[i + 1] = bkp; 
            aux = rest;
            rest = ft_strdup(&rest[i + 1]); 
            free(aux);
            return (line);
        }
    }
    line = malloc(BUFFER_SIZE + 1);
    while (bytes_read > 0)
    {
        bytes_read = read(fd, line, BUFFER_SIZE);
        if (bytes_read < 0)
        {
            free(line);
            free(rest);
            rest = NULL;
            return (NULL);
        }
        line[bytes_read] = '\0';
        if (bytes_read == 0)
            break;
        rest = ft_realloc(rest, line);
        i = 0;
        while (line[i] != '\n' && line[i] != '\0')
            i++;
        if (line[i] == '\n')
        {
            break ;
        }
    }
    free(line);
    if (rest == NULL)
        return (NULL);
    i = 0;
    while (rest[i] != '\n' && rest[i] != '\0')
        i++;
    if (rest[i] == '\n')
    {
        char    bkp = rest[i + 1];
        rest[i + 1] = '\0';
        line = ft_strdup(rest);
        if (!line)
        {
            free(rest);
            rest = NULL;
            return (NULL);
        }
        rest[i + 1] = bkp;
        aux = rest;
        rest = ft_strdup(&rest[i + 1]);
        free(aux);
    }
    else
    {
        line = rest;
        rest = NULL;
    }
    return (line);
}

int	main(int argc, char *argv[])
{
	int		fd;
	int		line;
	char	*lines[15];

	if (argc != 2)
	{
		puts("Make the L!");
		return (1);
	}
	// Fazer validação .cub
	fd = open(argv[1], O_RDONLY);
	line = 0;
	while (line < 15)
		lines[line++] = get_next_line(fd);
	line = 0;
	while (lines[line])
	{
		printf("linha %2d|%s", line + 1, lines[line]);
		line++;
	}
	puts("");
	return (0);
}