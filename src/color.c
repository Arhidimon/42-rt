/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezruch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 12:58:23 by dbezruch          #+#    #+#             */
/*   Updated: 2018/09/30 12:58:26 by dbezruch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		multcolor(float value, int color)
{
	unsigned char r;
	unsigned char g;
	unsigned char b;

	r = value * ((color & 16711680) >> 16);
	g = value * ((color & 65280) >> 8);
	b = value * ((color & 255));
	if (value > 1)
		return (color);
	return ((r << 16) + (g << 8) + b);
}

int		sumcolor(float value, int c1, int c2)
{
	unsigned char r;
	unsigned char g;
	unsigned char b;

	r = value * ((c1 & 16711680) >> 16) + (1 - value) * ((c2 & 16711680) >> 16);
	g = value * ((c1 & 65280) >> 8) + (1 - value) * ((c2 & 65280) >> 8);
	b = value * ((c1 & 255)) + (1 - value) * (c2 & 255);
	return ((r << 16) + (g << 8) + b);
}
