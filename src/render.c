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
#include <gtk/gtk.h>

t_vector	canvas_to_viewport(int x, int y)
{
	t_vector v;

	v[0] = x * (float)VIEWPORT_WIDTH / SCREEN_WIDTH / g_app->screen.ssvalue;
	v[1] = y * (float)VIEWPORT_HEIGHT / SCREEN_HEIGHT / g_app->screen.ssvalue;
	v[2] = g_app->camera.fov;
	return (v);
}

void		render()
{
	int			x;
	int			y;
	t_ray		ray;
	t_vector	d;

	g_stoprendering = 0;
	x = -1;
	while (++x < SCREEN_WIDTH * g_app->screen.ssvalue)
	{
		y = -1;
		while (++y < SCREEN_HEIGHT * g_app->screen.ssvalue)
		{
			d = rotate(g_app->camera.direction, canvas_to_viewport(
				x - SCREEN_WIDTH *g_app->screen.ssvalue / 2,
					SCREEN_HEIGHT *g_app->screen.ssvalue / 2 - y));
			ray.position = g_app->camera.position;
			ray.direction = d;
			g_app->screen.sspixels[x + y * SCREEN_WIDTH * g_app->screen.ssvalue] =
					trace_ray(&ray, 1, g_app->iterations);
		}
		if (g_stoprendering)
			return;
		gtk_progress_bar_set_fraction((GtkProgressBar *)g_app->progressbar, (double)x / (SCREEN_WIDTH * g_app->screen.ssvalue));
		while (g_main_context_iteration(NULL, FALSE));		
	}
	ssaa();
	gtk_widget_queue_draw(g_app->da);
}
