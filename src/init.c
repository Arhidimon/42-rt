/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezruch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 13:49:26 by dbezruch          #+#    #+#             */
/*   Updated: 2019/01/14 19:50:53 by atikhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	initialize_app(void)
{
	GError		*error = NULL;
	const char	*filename = "earthmap1k.jpg";

	g_app = malloc(sizeof(t_app));
	
	g_app->texture = NULL;
	g_app->texture = gdk_pixbuf_new_from_file(filename, &error);
	g_app->raw_text = gdk_pixbuf_read_pixels(g_app->texture);
	g_app->text_h = gdk_pixbuf_get_width(g_app->texture);
	g_app->text_w = gdk_pixbuf_get_height(g_app->texture);
/*
	for (int i = 0; i < g_app->text_h; i++)
	{
		for (int j = 0; j < g_app->text_w; j++)
		{
			printf("%s ", g_app->raw_text);
		}
		printf("\n");
	}
*/
	g_app->screen.ssvalue = SS_VALUE;
	g_app->screen.pixels = malloc(sizeof(int32_t) * (int)(SCREEN_WIDTH
			* SCREEN_HEIGHT));
	g_app->screen.sspixels = malloc(sizeof(int32_t) * (int)(SCREEN_WIDTH
			* SCREEN_HEIGHT) * g_app->screen.ssvalue * g_app->screen.ssvalue);
	g_app->scene.rays = malloc(sizeof(t_ray) * (int)(SCREEN_WIDTH
			* SCREEN_HEIGHT));
	g_app->camera.position = (t_vector) {0, 0, -3};
	g_app->camera.fov = FOV;
	g_app->camera.direction = (t_vector) {0, 0, 0};
	g_app->iterations = MAX_ITERS;
	g_app->shadow = 1;
	g_app->light = 1;
	g_app->curobj = g_app->scene.primitives;
	g_app->curobjtype = CAMERA;
}

