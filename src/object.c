/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezruch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 13:26:56 by dbezruch          #+#    #+#             */
/*   Updated: 2018/09/30 13:26:58 by dbezruch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		next_obj(t_app *app)
{
	if (app->curobjtype == PRIMITIVE && app->curobj->next)
		app->curobj = app->curobj->next;
	else if (app->curobjtype == LIGHT && app->curlobj->next)
		app->curlobj = app->curlobj->next;
}

void		prev_obj(t_app *app)
{
	if (app->curobjtype == PRIMITIVE && app->curobj->prev)
		app->curobj = app->curobj->prev;
	else if (app->curobjtype == LIGHT && app->curlobj->prev)
		app->curlobj = app->curlobj->prev;
}

t_vector	*get_curobj_pos(t_app *app)
{
	if (app->curobjtype == CAMERA)
		return (&(app->camera.position));
	else if (app->curobjtype == LIGHT)
		return (&(app->curlobj->vector));
	else if (app->curobj->type == SPHERE)
		return (&(app->curobj->p.sphere.position));
	else if (app->curobj->type == CONE)
		return (&(app->curobj->p.cone.position));
	else if (app->curobj->type == PLANE)
		return (&(app->curobj->p.plane.position));
	else
		return (&(app->curobj->p.cylinder.position));
}

t_vector	*get_curobj_dir(t_app *app)
{
	if (app->curobjtype == CAMERA)
		return (&(app->camera.direction));
	else if (app->curobjtype == PRIMITIVE)
	{
		if (app->curobj->type == SPHERE)
			return (&(app->curobj->rotation));
		else if (app->curobj->type == CONE)
			return (&(app->curobj->rotation));
		else if (app->curobj->type == PLANE)
			return (&(app->curobj->p.plane.normal));
		else
			return (&(app->curobj->rotation));
	}
	else
		return (&(app->curlobj->vector));
}
