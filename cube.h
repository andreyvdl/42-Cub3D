
#ifndef CUBE_H
# define CUBE_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

// Utils.c
size_t	ft_strlen(const char *s);
char	*ft_strdup(char *s);
char	*ft_strrchr(char *s, int c);
char	*ft_strchr(char *s, int c);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strtrim(char *s1, char *set);
int		ft_isdigit(int c);
size_t	ft_matrixlen(char **matrix);
void	ft_free_matrix(void **matrix);
void	free_local_matrix(char *matrix[]);
int		ft_atoi(const char *nptr);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);

// ft_split.c
char	**ft_split(const char *s, char c);

// get_next_line.c
char	*ft_realloc(char *s1, char *s2);
char	*get_next_line(int fd);

#endif
