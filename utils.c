#include "mlx_test.h"

double	rad_overflow(double radians)
{
	if (radians < 0)
		return (radians + RAD_360);
	if (radians > RAD_360)
		return (radians - RAD_360);
	return (radians);
}

int	start_looking_fix(int angle)
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
	fisheye = rad_overflow(fisheye);
	return (cos(fisheye));
}

double	pythagoras(double x0, double y0, double x1, double y1)
{
	return (sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0)));
}
