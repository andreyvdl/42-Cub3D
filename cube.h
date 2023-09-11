
#ifndef CUBE_H
# define CUBE_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

// Utils.c
size_t	ft_strlen(char *s);
char	*ft_strdup(char *s);
char	*ft_strrchr(char *s, int c);
char	*ft_strchr(char *s, int c);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, size_t n);
char	*ft_strtrim(char *s1, char *set);
int		ft_isdigit(int c);
size_t	ft_matrixlen(char **matrix);
void	ft_free_matrix(void **matrix);

// ft_split.c
char	**ft_split(char *s, char c);

// get_next_line.c
char	*ft_realloc(char *s1, char *s2);
char	*get_next_line(int fd);

#endif
