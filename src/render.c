/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezruch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 15:50:27 by dbezruch          #+#    #+#             */
/*   Updated: 2018/09/25 15:50:29 by dbezruch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"
#include "pthread.h"

t_vector	canvas_to_viewport(t_app *app, int x, int y)
{
	t_vector v;

	v[0] = x * (float)VIEWPORT_WIDTH / SCREEN_WIDTH / app->screen.ssvalue;
	v[1] = y * (float)VIEWPORT_HEIGHT / SCREEN_HEIGHT / app->screen.ssvalue;
	v[2] = app->camera.fov;
	return (v);
}

void		render(t_app *app)
{
	int			x;
	int			y;
	t_ray		ray;
	t_vector	d;

	x = -1;
	while (++x < SCREEN_WIDTH * app->screen.ssvalue)
	{
		y = -1;
		while (++y < SCREEN_HEIGHT * app->screen.ssvalue)
		{
			d = rotate(app->camera.direction, canvas_to_viewport(app,
					x - SCREEN_WIDTH * app->screen.ssvalue / 2,
					SCREEN_HEIGHT * app->screen.ssvalue / 2 - y));
			ray.position = app->camera.position;
			ray.direction = d;
			app->screen.sspixels[x + y * SCREEN_WIDTH * app->screen.ssvalue] =
					trace_ray(app, &ray, 1, app->iterations);
		}
	}
	ssaa(app);
}
