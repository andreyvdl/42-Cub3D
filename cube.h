
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
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*ft_strrchr(char *s, int c);
int		ft_strcmp(char *s1, char *s2);

// get_next_line.c
char	*ft_realloc(char *s1, char *s2);
char	*get_next_line(int fd);

#endif