/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezruch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 15:42:11 by dbezruch          #+#    #+#             */
/*   Updated: 2018/06/29 15:42:14 by dbezruch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int		shadow(t_vector p, t_light *current, t_ray ray)
{
	t_primitive *shadow;
	float		t;

	if (g_app->shadow)
	{
		shadow = g_app->scene.primitives;
		t = closest_intersection(&ray, 0.001, &shadow);
		t = calc_distance(ray.position + mult_vector(ray.direction, t), p);
		if (shadow && t <= calc_distance(current->vector, p))
			return (1);
	}
	return (0);
}

float	computeshine(t_vector l, t_vector n, t_vector v)
{
	t_vector	r;
	float		d_rv;
	float		d_nl;
	float		i;

	i = 0;
	d_nl = dotproduct(n, l);
	if (d_nl > 0)
		i += g_app->curl->intensity * d_nl / (calc_magnitude(&n) *
				calc_magnitude(&l));
	if (g_app->tempfloat != -1)
	{
		r = reflect_ray(l, n);
		d_rv = dotproduct(r, v);
		if (d_rv > 0)
			i += g_app->curl->intensity * powf(d_rv / ((calc_magnitude(&r) *
					calc_magnitude(&v))),
					g_app->tempfloat);
	}
	return (i);
}

float	computelight(t_vector p, t_vector n, t_vector v)
{
	t_vector	l;
	float		i;
	t_ray		ray;

	i = 0;
	g_app->curl = g_app->scene.lights;
	while (g_app->curl)
	{
		if (g_app->curl->type == AMBIENT)
			i += g_app->curl->intensity;
		else
		{
			l = ((g_app->curl->type == POINT) ? g_app->curl->vector - p :
					g_app->curl->vector);
			ray.direction = l;
			ray.position = p;
			if (shadow(p, g_app->curl, ray) && ((g_app->curl = g_app->curl->next)
			|| 1))
				continue;
			i += computeshine(l, n, v);
		}
		g_app->curl = g_app->curl->next;
	}
	return (i);
}
