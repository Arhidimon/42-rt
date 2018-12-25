/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezruch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 19:33:15 by dbezruch          #+#    #+#             */
/*   Updated: 2018/09/25 19:33:17 by dbezruch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_vector	reflect_ray(t_vector r, t_vector n)
{
	return (mult_vector(n, 2 * dotproduct(n, r)) - r);
}

int			reflection(t_app *app, t_ray *ray, t_vector n, int depth)
{
	t_vector	r;
	t_ray		rray;

	r = reflect_ray(-(ray->direction), n);
	rray.position = app->tv + mult_vector(r, 0.001);
	rray.direction = reflect_ray(-(ray->direction), n);
	return (trace_ray(app, &rray, 0.001, depth - 1));
}

t_vector	get_normal(t_app *app, t_primitive *closest_obj, t_ray *ray,
		float closest_t)
{
	t_vector	p;

	p = ray->position + mult_vector(ray->direction, closest_t);
	if (closest_obj->type == SPHERE)
		app->tempvector = p - closest_obj->p.sphere.position;
	else if (closest_obj->type == PLANE)
		app->tempvector = closest_obj->p.plane.normal;
	else if (closest_obj->type == CYLINDER)
		app->tempvector = p - closest_obj->p.cylinder.position -
				mult_vector(closest_obj->rotation, TEMP_M);
	else
		app->tempvector = p - closest_obj->p.cone.position -
				mult_vector(closest_obj->rotation,
				(powf(tanf(closest_obj->p.cone.angle), 2) + 1) * TEMP_M1);
	return (p);
}

int			trace_ray(t_app *app, t_ray *ray, float min, int depth)
{
	float		closest_t;
	int			color;
	t_primitive	*closest_obj;

	closest_obj = NULL;
	closest_t = closest_intersection(app, ray, min, &closest_obj);
	if (closest_obj == NULL)
		return (BG_COLOR);
	if (!app->light)
		return (closest_obj->color);
	app->tv = get_normal(app, closest_obj, ray, closest_t);
	app->tempfloat = closest_obj->specular;
	color = multcolor(computelight(app, app->tv + mult_vector(-(ray->direction),
	0.00001), app->tempvector, -(ray->direction)), closest_obj->color);
	return ((depth <= 0 || closest_obj->reflection <= 0) ? color :
	sumcolor(closest_obj->reflection, reflection(app, ray, app->tempvector,
			depth), color));
}
