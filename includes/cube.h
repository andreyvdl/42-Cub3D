
#ifndef CUBE_H
# define CUBE_H

# include <fcntl.h>
# include <math.h>
//# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include "defines.h"
//# include <limits.h>

enum e_attributes
{
	NO = 0,
	SO,
	WE,
	EA
};

enum e_colors
{
	R = 0,
	G,
	B,
	A
};

enum e_positions
{
	X = 0,
	Y
};

typedef struct s_mlx
{
	char			**attributes;
	mlx_texture_t	*tex[4];
	mlx_image_t		*img;
	mlx_t			*win;
	bool			m_cntl;
	uint32_t		ceil;
	uint32_t		floor;
}	t_mlx;

typedef struct s_wall_parameters
{
	double	height;
	int		init;
	int		ray_x;
}	t_wall;


// attributes_functions.c
void			adjust_attributes(char *textures[]);
int				got_new_attribute(char *textures[], char **elements, char *new);
int				get_view_attributes(char *textures[], char *filename);

// cast_rays.c
void			update_distance(double *x, double *y, double *ray, double *off);
double			cost_y_ray_distance(double *x, double *y, double tangent, \
									double ray_angle);
double			cost_x_ray_distance(double *x, double *y, double tangent, \
									double ray_angle);
mlx_texture_t	*texture_ternary(mlx_texture_t *cond1, mlx_texture_t *cond2, \
								bool result);
void			cast_rays(t_mlx *mlx, int pixel, int width_sz);

// draw_wall.c
uint32_t		tex_to_col(mlx_texture_t *tex, int x, int y);
void			draw_wall(t_mlx *mlx, t_wall wall, mlx_texture_t *tex);

// element_functions.c
int				validate_element(char *line);
void			normalize_element(char *start);
int				element_checker(char *filename);

// error_message.c
int				you_made_the_l(char *str);

// ft_atoi.c
int				ft_isdigit(int c);
int				ft_atoi(const char *nptr);

// ft_split.c
char			**ft_split(const char *s, char c);

// get_next_line.c
char			*get_next_line(int fd);

// has_invalid_functions.c
int				has_invalid_character(char **map);
int				has_invalid_number_of_players(char **map);
int				has_invalid_walls(char **map);
int				has_invalid_color(char **lines);
int				has_invalid_number(char *str);

// keyboard.c
void			movement_keys(t_mlx *mlx);
void			keyboard(mlx_key_data_t data, void *var);

// map_functions.c
int				count_map_lines(int fd, int map_lines, int itens_ignore, \
								int map_start);
char			**do_the_map(int fd, int map_lines);
int				map_normalizer(char **map);
int				validate_map(char **map);
char			**get_map(char *filename);

// mouse.c
void			toggle_mouse(t_mlx *mlx);
void			mouse(double x_pos, double y_pos, void *var);

// player_globals.c
double			*getter_player_x(void);
double			*getter_player_y(void);
int				*getter_player_ang(void);
double			*getter_dir_x(void);
double			*getter_dir_y(void);

// render.c
void			draw_background(t_mlx *mlx);
void			draw_direction(t_mlx *mlx, double x0, double y0);
void			draw_player(t_mlx *mlx);
void			draw_map(t_mlx *mlx, int map_x, int map_y);
void			draw_aim(t_mlx *mlx);
void			render(void *var);

// visual_start.c
bool			load_textures(t_mlx *mlx);
void			free_mlx(t_mlx *mlx);
int				free_mlx_error(t_mlx *mlx);
int				make_it_visual(t_mlx *mlx, int vision_dir);

// world_globals.c
char			***getter_map(void);
mlx_texture_t	**getter_tex(void);

// map_utils.c
int				all_chars_is_in_set(char *arg, char *set);
size_t			find_and_count(char *str, char c);
int				is_only_spaces(char *line);
char			*do_the_new_line(char *line, size_t new_size);
void			remove_newline_and_carriage(char **map);

// math_utils.c
double			rad_overflow(double radians);
void			change_pos(double x, double y);
double			fisheye_fix(double ray_angle);
double			pythagoras(double x0, double y0, double x1, double y1);

// matrix_utils.c
size_t			ft_matrixlen(char **matrix);
void			ft_free_matrix(void **matrix);
void			free_local_matrix(char *matrix[]);

// mem_utils.c
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memset(void *s, int c, size_t n);

// str_utils.c
size_t			ft_strlen(const char *s);
char			*ft_strdup(char *s);
char			*ft_strrchr(char *s, int c);
char			*ft_strchr(char *s, int c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);

// str_utils2.c
char			*ft_strtrim(char *s1, char *set);
int				ft_strcmp(char *s1, char *s2);
void			ft_putendl_fd(int fd, char *str);

#endif
