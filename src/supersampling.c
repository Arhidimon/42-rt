/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supersampling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezruch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 21:25:52 by dbezruch          #+#    #+#             */
/*   Updated: 2018/05/12 21:25:53 by dbezruch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int		rgb_to_int(unsigned char red, unsigned char green, unsigned char blue)
{
	return (((red << 16) | (green << 8) | blue));
}

int		ssaacalc(t_app *app, int x, int y, int temp)
{
	int			x1;
	int			y1;
	long int	r;
	long int	g;
	long int	b;

	r = 0;
	g = 0;
	b = 0;
	x1 = -1;
	while (++x1 < app->screen.ssvalue)
	{
		y1 = -1;
		while (++y1 < app->screen.ssvalue)
		{
			temp = app->screen.sspixels[app->screen.ssvalue * x + x1 +
					app->screen.ssvalue * SCREEN_WIDTH *
					(app->screen.ssvalue * y + y1)];
			r += (temp & (255 << 16)) >> 16;
			g += (temp & (255 << 8)) >> 8;
			b += temp & (255);
		}
	}
	return (rgb_to_int(r / SS_SQ, g / SS_SQ, b / SS_SQ));
}

void	ssaa(t_app *app)
{
	int x;
	int y;
	int temp;

	temp = 0;
	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		y = -1;
		while (++y < SCREEN_HEIGHT)
		{
			app->screen.pixels[x + y * SCREEN_WIDTH] =
					ssaacalc(app, x, y, temp);
		}
	}
}
