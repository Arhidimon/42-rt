/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezruch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 14:10:11 by dbezruch          #+#    #+#             */
/*   Updated: 2018/09/30 14:10:18 by dbezruch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int		count_fps(t_app *app)
{
	float	fps;
	int32_t	i;
	int32_t	count;
	int32_t	getticks;
	int32_t	framestimesindex;

	fps = 0;
	framestimesindex = app->framecount % FRAME_VALUES;
	getticks = SDL_GetTicks();
	app->framestimes[framestimesindex] = getticks - app->frametimelast;
	app->frametimelast = getticks;
	app->framecount++;
	count = app->framecount < FRAME_VALUES ? app->framecount : FRAME_VALUES;
	i = 0;
	while (i < count)
		fps += app->framestimes[i++];
	fps /= count;
	fps = 1000.f / fps;
	return ((int)fps);
}

int		print_fps(t_app *app, float fps)
{
	char		*mtext;
	char		*mtext1;
	SDL_Surface *msur;
	SDL_Texture *mtexture;
	SDL_Rect	rect;

	mtext1 = ft_itoa((int)fps);
	mtext = ft_strjoin("FPS: ", mtext1);
	free(mtext1);
	msur = TTF_RenderUTF8_Blended(app->messagefont, mtext, app->messagecolor);
	if (msur == NULL)
		handle_sdl_error();
	mtexture = SDL_CreateTextureFromSurface(app->renderer, msur);
	if (mtexture == NULL || TTF_SizeUTF8(app->messagefont, mtext,
	&(app->messagewidth), &(app->messageheight)) == -1)
		handle_sdl_error();
	rect.x = 10;
	rect.y = 10;
	rect.w = app->messagewidth;
	rect.h = app->messageheight;
	SDL_RenderCopy(app->renderer, mtexture, NULL, &rect);
	SDL_DestroyTexture(mtexture);
	SDL_FreeSurface(msur);
	free(mtext);
	return (0);
}
