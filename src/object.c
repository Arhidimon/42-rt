/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezruch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 13:26:56 by dbezruch          #+#    #+#             */
/*   Updated: 2019/01/17 19:29:16 by atikhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		next_obj(void)
{
	if (g_app->curobjtype == PRIMITIVE && g_app->curobj->next)
		g_app->curobj = g_app->curobj->next;
	else if (g_app->curobjtype == LIGHT && g_app->curlobj->next)
		g_app->curlobj = g_app->curlobj->next;
}

void		prev_obj(void)
{
	if (g_app->curobjtype == PRIMITIVE && g_app->curobj->prev)
		g_app->curobj = g_app->curobj->prev;
	else if (g_app->curobjtype == LIGHT && g_app->curlobj->prev)
		g_app->curlobj = g_app->curlobj->prev;
}

t_vector	*get_curobj_pos(void)
{
	if (g_app->curobjtype == CAMERA)
		return (&(g_app->camera.position));
	else if (g_app->curobjtype == LIGHT)
		return (&(g_app->curlobj->vector));
	else if (g_app->curobj->type == SPHERE)
		return (&(g_app->curobj->p.sphere.position));
	else if (g_app->curobj->type == CONE)
		return (&(g_app->curobj->p.cone.position));
	else if (g_app->curobj->type == PLANE)
		return (&(g_app->curobj->p.plane.position));
	else
		return (&(g_app->curobj->p.cylinder.position));
}

t_vector	*get_curobj_dir(void)
{
	if (g_app->curobjtype == CAMERA)
		return (&(g_app->camera.direction));
	else if (g_app->curobjtype == PRIMITIVE)
	{
		if (g_app->curobj->type == SPHERE)
			return (&(g_app->curobj->rotation));
		else if (g_app->curobj->type == CONE)
			return (&(g_app->curobj->rotation));
		else if (g_app->curobj->type == PLANE)
			return (&(g_app->curobj->p.plane.normal));
		else
			return (&(g_app->curobj->rotation));
	}
	else
		return (&(g_app->curlobj->vector));
}
