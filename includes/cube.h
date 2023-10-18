
#ifndef CUBE_H
# define CUBE_H

# include <fcntl.h>
# include <math.h>
//# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../MLX42/include/MLX42/MLX42.h"
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
}	t_mlx;

//============================ render.c =============================
void	draw_background(t_mlx *mlx);
void	draw_direction(t_mlx *mlx, double x0, double y0);
void	draw_player(t_mlx *mlx);
void	draw_map(t_mlx *mlx, int map_x, int map_y);
void	draw_aim(t_mlx *mlx);
void	render(void *var);

//========================== cast_rays.c ============================
double	cost_y_ray_distance(double *x, double *y, double tangent, \
							double ray_angle);
double	cost_x_ray_distance(double *x, double *y, double tangent, \
							double ray_angle);
void	update_distance(double *x, double *y, double *ray, double *off);
void	draw_wall(t_mlx *mlx, double height, int init, int ray_x, 
					mlx_texture_t *tex);
void	cast_rays(t_mlx *mlx, int fov);

//=========================== utils.c ================================
double	rad_overflow(double radians);
double	fisheye_fix(double ray_angle);
double	pythagoras(double x0, double y0, double x1, double y1);
void	change_pos(double x, double y);

//========================== mouse.c =================================
void	toggle_mouse(t_mlx *mlx);
void	mouse(double x_pos, double y_pos, void *var);

//========================= keyboard.c ===============================
void	movement_keys(t_mlx *mlx);
void	keyboard(mlx_key_data_t data, void *var);

//======================= fake_globals.c =============================
double	*getter_player_x(void);
double	*getter_player_y(void);
int		*getter_player_ang(void);
double	*getter_dir_x(void);
double	*getter_dir_y(void);

char	***g_map(void);

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
void	put_map_on_screen(void *tudo);

// ft_split.c
char	**ft_split(const char *s, char c);

// get_next_line.c
char	*ft_realloc(char *s1, char *s2);
char	*get_next_line(int fd);

#endif
