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

t_app	*initialize_app(void)
{
	t_app *app;

	app = malloc(sizeof(t_app));
	app->screen.ssvalue = SS_VALUE;
	app->screen.pixels = malloc(sizeof(int32_t) * (int)(SCREEN_WIDTH
			* SCREEN_HEIGHT));
	app->screen.sspixels = malloc(sizeof(int32_t) * (int)(SCREEN_WIDTH
			* SCREEN_HEIGHT) * app->screen.ssvalue * app->screen.ssvalue);
	app->scene.rays = malloc(sizeof(t_ray) * (int)(SCREEN_WIDTH
			* SCREEN_HEIGHT));
	app->camera.position = (t_vector) {0, 0, -3};
	app->camera.fov = FOV;
	app->camera.direction = (t_vector) {0, 0, 0};
	app->iterations = MAX_ITERS;
	app->shadow = 1;
	app->light = 1;
	app->curobj = app->scene.primitives;
	app->curobjtype = CAMERA;
	return (app);
}

