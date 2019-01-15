/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezruch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 13:16:34 by dbezruch          #+#    #+#             */
/*   Updated: 2018/09/30 13:16:37 by dbezruch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

float		intersect_sphere(t_primitive *primitive, t_ray *ray)
{
	t_vector	k;
	t_roots		r;

	k = ray->position - primitive->p.sphere.position;
	r = solve_qe(dotproduct(ray->direction, ray->direction),
			2 * dotproduct(k, ray->direction),
			dotproduct(k, k) - primitive->p.sphere.radius2);
	return (MIN(r[0], r[1]) > 0 ? MIN(r[0], r[1]) : MAX(r[0], r[1]));
}

float		intersect_plane(t_primitive *primitive, t_ray *ray)
{
	t_vector	k;
	float		dot;

	dot = dotproduct(primitive->p.plane.normal, ray->direction);
	if (dot != 0)
	{
		k = primitive->p.plane.position - ray->position;
		return (dotproduct(k, primitive->p.plane.normal) / dot);
	}
	return (-1);
}

float		intersect_cylinder(t_primitive *primitive, t_ray *ray)
{
	float		a;
	float		b;
	float		c;
	t_vector	k;
	t_roots		t;

	primitive->rotation = normalize(primitive->rotation);
	k = ray->position - primitive->p.cylinder.position;
	a = dotproduct(ray->direction, ray->direction) -
			powf(dotproduct(ray->direction, primitive->rotation), 2);
	b = 2 * (dotproduct(ray->direction, k) - dotproduct(ray->direction,
			primitive->rotation) * dotproduct(k, primitive->rotation));
	c = dotproduct(k, k) - powf(dotproduct(k, primitive->rotation), 2) -
			primitive->p.cylinder.radius2;
	t = solve_qe(a, b, c);
	return ((t[0] > 0) ? t[0] : t[1]);
}

float		intersect_cone(t_primitive *primitive, t_ray *ray)
{
	float		a;
	float		b;
	float		c;
	t_vector	k;
	t_roots		t;

	primitive->rotation = normalize(primitive->rotation);
	k = ray->position - primitive->p.cone.position;
	a = dotproduct(ray->direction, ray->direction) -
			(powf(tanf(primitive->p.cone.angle), 2) + 1) *
			powf(dotproduct(ray->direction, primitive->rotation), 2);
	b = 2 * (dotproduct(ray->direction, k) -
			(powf(tanf(primitive->p.cone.angle), 2) + 1) *
			dotproduct(ray->direction, primitive->rotation) * dotproduct(k,
					primitive->rotation));
	c = dotproduct(k, k) - (powf(tanf(primitive->p.cone.angle), 2) + 1) *
			powf(dotproduct(k, primitive->rotation), 2);
	t = solve_qe(a, b, c);
	return ((t[0] > 0) ? t[0] : t[1]);
}

float		closest_intersection(t_ray *ray, float tmin,
		t_primitive **object)
{
	float		closest_t;
	float		t;
	t_primitive	*closest_obj;
	t_primitive	*current;

	closest_t = INFINITY;
	closest_obj = NULL;
	current = g_app->scene.primitives;
	while (current)
	{
		if ((current->type == SPHERE && INT_SPH) ||
		(current->type == PLANE && INT_PL) ||
		(current->type == CYLINDER && INT_CYL) ||
		(current->type == CONE && INT_CON))
		{
			closest_obj = current;
			closest_t = t;
		}
		current = current->next;
	}
	*object = (closest_t == INFINITY) ? NULL : closest_obj;
	return (closest_t);
}
