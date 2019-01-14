/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezruch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 13:49:26 by dbezruch          #+#    #+#             */
/*   Updated: 2018/09/30 13:49:28 by dbezruch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	initialize_app(void)
{
	g_app = malloc(sizeof(t_app));
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
	g_app->curlobj = g_app->scene.lights;
	g_app->curobjtype = CAMERA;
}

