/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezruch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 18:48:16 by dbezruch          #+#    #+#             */
/*   Updated: 2018/09/25 15:16:37 by dbezruch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static	SDL_Scancode g_key = 0;

void	key_handler3(t_app *app)
{
	if (g_key == SDL_SCANCODE_HOME)
		app->curobjtype = (app->curobjtype == LIGHT ? CAMERA :
				app->curobjtype - 1);
	else if (g_key == SDL_SCANCODE_END)
		app->curobjtype = (app->curobjtype == CAMERA ? LIGHT :
				app->curobjtype + 1);
	else if (g_key == SDL_SCANCODE_PAGEDOWN)
		next_obj(app);
	else if (g_key == SDL_SCANCODE_PAGEUP)
		prev_obj(app);
	else if (g_key == SDL_SCANCODE_Z)
		app->curobj = add_plane(&(app->scene.primitives), (t_vector) {0, 0, 0},
				(t_vector) {0, 1, 0}, rand() % 0xFFFFFF);
	else if (g_key == SDL_SCANCODE_X)
		app->curobj = add_cone(&(app->scene.primitives), (t_vector) {0, 0, 0},
				(t_vector) {0, 1, 0}, rand() % 0xFFFFFF);
	else if (g_key == SDL_SCANCODE_C)
		app->curobj = add_cylinder(&(app->scene.primitives), (t_ray){{0, 0, 0},
		{0, 1, 0}}, 1, rand() % 0xFFFFFF);
	else if (g_key == SDL_SCANCODE_V)
		app->curobj = add_sphere(&(app->scene.primitives),
				(t_vector) {0, 0, 0}, 1, rand() % 0xFFFFFF);
	render(app);
}

void	key_handler2(t_app *app)
{
	if (g_key == SDL_SCANCODE_W)
		(*(get_curobj_dir(app)))[0] -= CAMERA_ROTATE;
	else if (g_key == SDL_SCANCODE_S)
		(*(get_curobj_dir(app)))[0] += CAMERA_ROTATE;
	else if (g_key == SDL_SCANCODE_A)
		(*(get_curobj_dir(app)))[1] -= CAMERA_ROTATE;
	else if (g_key == SDL_SCANCODE_D)
		(*(get_curobj_dir(app)))[1] += CAMERA_ROTATE;
	else if (g_key == SDL_SCANCODE_Q)
		(*(get_curobj_dir(app)))[2] -= CAMERA_ROTATE;
	else if (g_key == SDL_SCANCODE_E)
		(*(get_curobj_dir(app)))[2] += CAMERA_ROTATE;
	else if (g_key == SDL_SCANCODE_EQUALS)
		app->iterations++;
	else if (g_key == SDL_SCANCODE_MINUS && app->iterations != 0)
		app->iterations--;
	else if (g_key == SDL_SCANCODE_BACKSPACE)
		TOGGLE(app->shadow);
	else if (g_key == SDL_SCANCODE_KP_ENTER)
		TOGGLE(app->light);
	else
		key_handler3(app);
	render(app);
}

void	key_handler1(t_app *app)
{
	if (g_key == KEY_NONE)
		return ;
	else if (g_key == SDL_SCANCODE_LEFT)
		*(get_curobj_pos(app)) -= rotate(app->camera.direction,
									(t_vector) {CAMERA_MOVE, 0, 0});
	else if (g_key == SDL_SCANCODE_RIGHT)
		*(get_curobj_pos(app)) += rotate(app->camera.direction,
									(t_vector) {CAMERA_MOVE, 0, 0});
	else if (g_key == SDL_SCANCODE_SPACE)
		*(get_curobj_pos(app)) += rotate(app->camera.direction,
									(t_vector) {0, CAMERA_MOVE, 0});
	else if (g_key == SDL_SCANCODE_TAB)
		*(get_curobj_pos(app)) -= rotate(app->camera.direction,
									(t_vector) {0, CAMERA_MOVE, 0});
	else if (g_key == SDL_SCANCODE_DOWN)
		*(get_curobj_pos(app)) -= rotate(app->camera.direction,
									(t_vector) {0, 0, CAMERA_MOVE});
	else if (g_key == SDL_SCANCODE_UP)
		*(get_curobj_pos(app)) += rotate(app->camera.direction,
									(t_vector) {0, 0, CAMERA_MOVE});
	else
		key_handler2(app);
	render(app);
}

void	key_handler(SDL_Scancode key_sc)
{
	g_key = key_sc;
}
