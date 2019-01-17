/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezruch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 19:33:15 by dbezruch          #+#    #+#             */
/*   Updated: 2019/01/13 17:49:58 by atikhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_vector	reflect_ray(t_vector r, t_vector n)
{
	return (mult_vector(n, 2 * dotproduct(n, r)) - r);
}

int			reflection(t_ray *ray, t_vector n, int depth)
{
	t_vector	r;
	t_ray		rray;

	r = reflect_ray(-(ray->direction), n);
	rray.position = g_app->tv + mult_vector(r, 0.001);
	rray.direction = reflect_ray(-(ray->direction), n);
	return (trace_ray(&rray, 0.001, depth - 1));
}

t_vector	norm_box(t_primitive *primitive, t_ray *ray, float closest_t)
{
	t_vector localPoint;
	t_vector norm;
	float distance;
	int i;

	i = -1;
	localPoint = ray->position + mult_vector(normalize(ray->direction),
		closest_t);
	while (++i < 3)
	{
		distance = fabs(primitive->p.box.radius - fabs(localPoint[i]));
		if (distance < closest_t)
		{
			closest_t = distance;
			if (i == 0)
				norm = (t_vector){0, 0, 1};
			if (i == 1)
				norm = (t_vector){1, 0, 0};
			if (i == 2)
				norm = (t_vector){0, 1, 0};
			return (norm);
		}
	}
	return (norm);
}

t_vector	get_normal(t_primitive *closest_obj, t_ray *ray,
		float closest_t)
{
	t_vector	p;

	p = ray->position + mult_vector(ray->direction, closest_t);
	if (closest_obj->type == SPHERE)
		g_app->tempvector = p - closest_obj->p.sphere.position;
	else if (closest_obj->type == PLANE)
		g_app->tempvector = closest_obj->p.plane.normal;
	else if (closest_obj->type == CYLINDER)
		g_app->tempvector = p - closest_obj->p.cylinder.position -
				mult_vector(closest_obj->rotation, TEMP_M);
	else if (closest_obj->type == TRIAN)
		g_app->tempvector = normalize(closest_obj->p.trian.normal);
	else if (closest_obj->type == BOX)
		g_app->tempvector = norm_box(closest_obj, ray, closest_t);
	else
		g_app->tempvector = p - closest_obj->p.cone.position -
				mult_vector(closest_obj->rotation,
				(powf(tanf(closest_obj->p.cone.angle), 2) + 1) * TEMP_M1);
	return (p);
}


int			get_text(t_primitive *obj, t_ray *ray, float clos_t)
{
	// int			color;
	// float		u;
	// float		v;
	// t_vector	point;
	// t_vector	norm;

// 	if (obj->type == SPHERE)
// 	{
		
// //		const guint8 *raw_text = gdk_pixbuf_read_pixels(texture);
// 		point = mult_vector((ray->position + ray->direction), clos_t);
// 		norm = normalize(obj->position - point);
// //		printf("norm: x:%f y:%f z:%f\n", norm[0], norm[1], norm[2], norm[3]);
// 		u = 0.5 + atan2(norm[2] , norm[0]) / (2 * M_PI);
// 		v = 0.5 - asin(norm[1]) / M_PI;
// //		printf("u: %f v:%f\n", u, v);
// //		float x = (float)(gdk_pixbuf_get_width(texture));
// //		float y = (float)(gdk_pixbuf_get_height(texture));
// //		printf("%f %f\n", x, y);
// //		color = raw_text[(int)(u * x * v * y + u * x)];
// 		return(color);
// 	}
// 	else
		return (obj->color);
}

int			trace_ray(t_ray *ray, float min, int depth)
{
	float		closest_t;
	int			color;
	t_primitive	*closest_obj;

	closest_obj = NULL;
	closest_t = closest_intersection(ray, min, &closest_obj);
	if (closest_obj == NULL)
		return (BG_COLOR);
	if (!g_app->light)
		return (closest_obj->color);
	g_app->tv = get_normal(closest_obj, ray, closest_t);
	g_app->tempfloat = closest_obj->specular;
	color = multcolor(computelight(g_app->tv + mult_vector(-(ray->direction),
	0.00001), g_app->tempvector, -(ray->direction)), closest_obj->color);
	return ((depth <= 0 || closest_obj->reflection <= 0) ? color :
	sumcolor(closest_obj->reflection, reflection(ray, g_app->tempvector,
			depth), color));
}
