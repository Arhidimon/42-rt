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

static	guint g_key = 0;

void	key_handler3(t_app *app)
{
	if (g_key == GDK_KEY_Home)
		app->curobjtype = (app->curobjtype == LIGHT ? CAMERA :
				app->curobjtype - 1);
	else if (g_key == GDK_KEY_End)
		app->curobjtype = (app->curobjtype == CAMERA ? LIGHT :
				app->curobjtype + 1);
	else if (g_key == GDK_KEY_Page_Down)
		next_obj(app);
	else if (g_key == GDK_KEY_Page_Up)
		prev_obj(app);
	else if (g_key == GDK_KEY_z)
		app->curobj = add_plane(&(app->scene.primitives), (t_vector) {0, 0, 0},
				(t_vector) {0, 1, 0}, rand() % 0xFFFFFF);
	else if (g_key == GDK_KEY_x)
		app->curobj = add_cone(&(app->scene.primitives), (t_vector) {0, 0, 0},
				(t_vector) {0, 1, 0}, rand() % 0xFFFFFF);
	else if (g_key == GDK_KEY_c)
		app->curobj = add_cylinder(&(app->scene.primitives), (t_ray){{0, 0, 0},
		{0, 1, 0}}, 1, rand() % 0xFFFFFF);
	else if (g_key == GDK_KEY_b)
		app->curobj = add_sphere(&(app->scene.primitives),
				(t_vector) {0, 0, 0}, 1, rand() % 0xFFFFFF);
	render(app);
}

void	key_handler2(t_app *app)
{
	if (g_key == GDK_KEY_w)
		(*(get_curobj_dir(app)))[0] -= CAMERA_ROTATE;
	else if (g_key == GDK_KEY_s)
		(*(get_curobj_dir(app)))[0] += CAMERA_ROTATE;
	else if (g_key == GDK_KEY_a)
		(*(get_curobj_dir(app)))[1] -= CAMERA_ROTATE;
	else if (g_key == GDK_KEY_d)
		(*(get_curobj_dir(app)))[1] += CAMERA_ROTATE;
	else if (g_key == GDK_KEY_q)
		(*(get_curobj_dir(app)))[2] -= CAMERA_ROTATE;
	else if (g_key == GDK_KEY_e)
		(*(get_curobj_dir(app)))[2] += CAMERA_ROTATE;
	else if (g_key == GDK_KEY_equal)
		app->iterations++;
	else if (g_key == GDK_KEY_minus && app->iterations != 0)
		app->iterations--;
	else if (g_key == GDK_KEY_BackSpace)
		TOGGLE(app->shadow);
	else if (g_key == GDK_KEY_KP_Enter)
		TOGGLE(app->light);
	else
		key_handler3(app);
	render(app);
}

void	key_handler1(t_app *app)
{
	if (g_key == GDK_KEY_Left)
		*(get_curobj_pos(app)) -= rotate(app->camera.direction,
									(t_vector) {CAMERA_MOVE, 0, 0});
	else if (g_key == GDK_KEY_Right)
		*(get_curobj_pos(app)) += rotate(app->camera.direction,
									(t_vector) {CAMERA_MOVE, 0, 0});
	else if (g_key == GDK_KEY_space)
		*(get_curobj_pos(app)) += rotate(app->camera.direction,
									(t_vector) {0, CAMERA_MOVE, 0});
	else if (g_key == GDK_KEY_Tab)
		*(get_curobj_pos(app)) -= rotate(app->camera.direction,
									(t_vector) {0, CAMERA_MOVE, 0});
	else if (g_key == GDK_KEY_Down)
		*(get_curobj_pos(app)) -= rotate(app->camera.direction,
									(t_vector) {0, 0, CAMERA_MOVE});
	else if (g_key == GDK_KEY_Up)
		*(get_curobj_pos(app)) += rotate(app->camera.direction,
									(t_vector) {0, 0, CAMERA_MOVE});
	else
		key_handler2(app);
	render(app);
}

void	key_handler(guint key_sc)
{
	g_key = key_sc;
}
