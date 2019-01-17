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

void	key_handler3(void)
{
	if (g_key == GDK_KEY_Home)
		g_app->curobjtype = (g_app->curobjtype == LIGHT ? CAMERA :
				g_app->curobjtype - 1);
	else if (g_key == GDK_KEY_End)
		g_app->curobjtype = (g_app->curobjtype == CAMERA ? LIGHT :
				g_app->curobjtype + 1);
	else if (g_key == GDK_KEY_Page_Down)
		next_obj();
	else if (g_key == GDK_KEY_Page_Up)
		prev_obj();
	else if (g_key == GDK_KEY_z)
		g_app->curobj = add_plane(&(g_app->scene.primitives),
			(t_vector){0, 0, 0}, (t_vector) {0, 1, 0}, rand() % 0xFFFFFF);
	else if (g_key == GDK_KEY_x)
		g_app->curobj = add_cone(&(g_app->scene.primitives),
			(t_vector){0, 0, 0}, (t_vector) {0, 1, 0}, rand() % 0xFFFFFF);
	else if (g_key == GDK_KEY_c)
		g_app->curobj = add_cylinder(&(g_app->scene.primitives),
			(t_ray){{0, 0, 0}, {0, 1, 0}}, 1, rand() % 0xFFFFFF);
	else if (g_key == GDK_KEY_b)
		g_app->curobj = add_sphere(&(g_app->scene.primitives),
				(t_vector) {0, 0, 0}, 1, rand() % 0xFFFFFF);
	g_stoprendering = 1;
	//render();
}

void	key_handler2(void)
{
	if (g_key == GDK_KEY_w)
		(*(get_curobj_dir()))[0] -= CAMERA_ROTATE;
	else if (g_key == GDK_KEY_s)
		(*(get_curobj_dir()))[0] += CAMERA_ROTATE;
	else if (g_key == GDK_KEY_a)
		(*(get_curobj_dir()))[1] -= CAMERA_ROTATE;
	else if (g_key == GDK_KEY_d)
		(*(get_curobj_dir()))[1] += CAMERA_ROTATE;
	else if (g_key == GDK_KEY_q)
		(*(get_curobj_dir()))[2] -= CAMERA_ROTATE;
	else if (g_key == GDK_KEY_e)
		(*(get_curobj_dir()))[2] += CAMERA_ROTATE;
	else if (g_key == GDK_KEY_equal)
		g_app->iterations++;
	else if (g_key == GDK_KEY_minus && g_app->iterations != 0)
		g_app->iterations--;
	else if (g_key == GDK_KEY_BackSpace)
		TOGGLE(g_app->shadow);
	else if (g_key == GDK_KEY_KP_Enter)
		TOGGLE(g_app->light);
	else
		key_handler3();
	//render();
}

void	key_handler1(void)
{
	if (g_key == GDK_KEY_Left)
		*(get_curobj_pos()) -= rotate(g_app->camera.direction,
									(t_vector) {CAMERA_MOVE, 0, 0});
	else if (g_key == GDK_KEY_Right)
		*(get_curobj_pos()) += rotate(g_app->camera.direction,
									(t_vector) {CAMERA_MOVE, 0, 0});
	else if (g_key == GDK_KEY_space)
		*(get_curobj_pos()) += rotate(g_app->camera.direction,
									(t_vector) {0, CAMERA_MOVE, 0});
	else if (g_key == GDK_KEY_Tab)
		*(get_curobj_pos()) -= rotate(g_app->camera.direction,
									(t_vector) {0, CAMERA_MOVE, 0});
	else if (g_key == GDK_KEY_Down)
		*(get_curobj_pos()) -= rotate(g_app->camera.direction,
									(t_vector) {0, 0, CAMERA_MOVE});
	else if (g_key == GDK_KEY_Up)
		*(get_curobj_pos()) += rotate(g_app->camera.direction,
									(t_vector) {0, 0, CAMERA_MOVE});
	else
		key_handler2();
	//render();
}

void	key_handler(guint key_sc)
{
	g_key = key_sc;
}
