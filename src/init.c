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
	app->messagecolor = (SDL_Color){255, 255, 255, 0};
	app->curobj = app->scene.primitives;
	app->curobjtype = CAMERA;
	return (app);
}

int		handle_sdl_error(void)
{
	ft_putendl(SDL_GetError());
	SDL_Quit();
	exit(0);
	return (1);
}

int		initialize_sdl(t_app *app)
{
	if (TTF_Init() == -1)
	{
		ft_putendl(TTF_GetError());
		return (1);
	}
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		handle_sdl_error();
	app->window = SDL_CreateWindow("RTv1 by dbezruch", SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (app->window == NULL)
		handle_sdl_error();
	app->renderer = SDL_CreateRenderer(app->window, -1,
	SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (app->renderer == NULL)
		handle_sdl_error();
	app->maintexture = SDL_CreateTexture(app->renderer,
	SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, SC_WH);
	if (app->maintexture == NULL)
		handle_sdl_error();
	app->messagefont = TTF_OpenFont("arial.ttf", FONT_SIZE);
	if (app->messagefont == NULL)
		handle_sdl_error();
	app->icon = SDL_LoadBMP("icon.bmp");
	SDL_SetWindowIcon(app->window, app->icon);
	return (0);
}
