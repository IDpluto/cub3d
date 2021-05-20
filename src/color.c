#include "cub3d.h"

int		create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int		get_t(int trgb)
{
	return (trgb & (0xFF << 24));
}

int		get_r(int trgb)
{
	return (trgb & (0xFF << 16));
}

int		get_g(int trgb)
{

	return (trgb & (0xFF << 8));
}

int		get_b(int trgb)
{
	return (trgb & (0xFF));
}



/*int fade_color( int color, double lum )
{
	lum = 0.7;
    int r, g, b;
    create_trgb(color, &r, &g, &b);
    return create_trgb(color, (int)(r*lum), (int)(g*lum), (int)(b*lum));
}
*/
