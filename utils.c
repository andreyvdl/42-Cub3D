#include "mlx_test.h"

int	angle_fix(int angle)
{
	if (angle > 90)
		return (360 - angle);
	else
		return (90 - angle);
}

void	change_pos(double x, double y)
{
	if (g_player_x + x > 1 \
	&& g_map[(int)(g_player_y / SIZE)][(int)((g_player_x + x) / SIZE)] != '1')
		g_player_x += x;
	if (g_player_y + y > 1 \
	&& g_map[(int)((g_player_y + y) / SIZE)][(int)(g_player_x / SIZE)] != '1')
		g_player_y += y;
}

double	fisheye_fix(double ray_angle)
{
	double	fisheye;

	fisheye = RAD_1 * g_player_angle - ray_angle;
	if (fisheye < 0)
		fisheye += RAD_360;
	else if (fisheye > RAD_360)
		fisheye -= RAD_360;
	return (cos(fisheye));
}

double	pythagoras(double x0, double y0, double x1, double y1)
{
	return (sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0)));
}
