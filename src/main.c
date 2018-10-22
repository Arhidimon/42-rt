/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezruch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 13:46:56 by dbezruch          #+#    #+#             */
/*   Updated: 2018/09/30 13:46:59 by dbezruch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int		event_handler(t_app *app)
{
	SDL_Event event;

	key_handler(KEY_NONE);
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			return (1);
		else if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
				return (1);
			else
				key_handler(event.key.keysym.scancode);
		}
	}
	key_handler1(app);
	return (0);
}

void	main_loop(t_app *app)
{
	app->framecount = 0;
	app->frametimelast = SDL_GetTicks();
	while (1)
	{
		if (event_handler(app))
			break ;
		clearinfo();
		printinfo(app);
		SDL_RenderClear(app->renderer);
		SDL_UpdateTexture(app->maintexture, NULL, app->screen.pixels,
		(int)SCREEN_WIDTH * sizeof(Uint32));
		SDL_RenderCopy(app->renderer, app->maintexture, NULL, NULL);
		print_fps(app, count_fps(app));
		SDL_RenderPresent(app->renderer);
	}
}

int		main(int argc, char **argv)
{
	t_app *app;

	app = initialize_app();
	initialize_sdl(app);
	if (argc > 1 && argv[1][0] == '1' && argv[1][1] == '\0')
		testscene_1(app);
	else if (argc > 1 && argv[1][0] == '2' && argv[1][1] == '\0')
		testscene_2(app);
	else if (argc > 1 && argv[1][0] == '3' && argv[1][1] == '\0')
		testscene_3(app);
	else if (argc > 1 && argv[1][0] == '4' && argv[1][1] == '\0')
		testscene_4(app);
	else
		testscene_5(app);
	printcontrols();
	app->curobj = app->scene.primitives;
	app->curlobj = app->scene.lights;
	printinfo(app);
	render(app);
	main_loop(app);
	SDL_DestroyTexture(app->maintexture);
	SDL_DestroyRenderer(app->renderer);
	SDL_DestroyWindow(app->window);
	SDL_Quit();
	return (0);
}
