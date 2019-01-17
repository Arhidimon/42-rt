/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_intersection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaznodi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 15:41:34 by vkaznodi          #+#    #+#             */
/*   Updated: 2019/01/14 15:41:36 by vkaznodi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		position_tri(t_primitive *primitive)
{
	t_vector	lol;
	t_vector	tri_rot;

	primitive->p.trian.a = (t_vector){(0 - primitive->p.trian.radius2), (0 -
		primitive->p.trian.radius2), 0 + 0.0001};
	primitive->p.trian.b = (t_vector){(0 + primitive->p.trian.radius2), (0 -
		primitive->p.trian.radius2), 0 + 0.0001};
	primitive->p.trian.c = (t_vector){0, (0 + primitive->p.trian.radius2),
		0 + 0.0001};
	lol = (t_vector){primitive->p.trian.normal[0], primitive->p.trian.normal[1],
		primitive->p.trian.normal[2] - 1};
	tri_rot[2] = 0;
	tri_rot[0] = (float)atan2(-lol[1], sqrt(lol[0] * lol[0] + lol[2] * lol[2]));
	tri_rot[1] = (float)atan2(lol[0], lol[2]);
	primitive->p.trian.a = rotate(tri_rot, primitive->p.trian.a) +
		primitive->p.trian.position;
	primitive->p.trian.b = rotate(tri_rot, primitive->p.trian.b) +
		primitive->p.trian.position;
	primitive->p.trian.c = rotate(tri_rot, primitive->p.trian.c) +
		primitive->p.trian.position;
}

void		position_box(t_primitive *primitive)
{
	primitive->p.box.a = (t_vector){(primitive->p.box.position[0]),
		(primitive->p.box.position[1]), primitive->p.box.position[2]};
	primitive->p.box.b = (t_vector){(primitive->p.box.position[0] +
		primitive->p.box.radius2), (primitive->p.box.position[1] +
		primitive->p.box.radius2), primitive->p.box.position[2] +
		primitive->p.box.radius2};
}

t_vector	vect(t_primitive *primitive, t_vector p, int i)
{
	if (i == 1)
		return (vecros(primitive->p.trian.b - primitive->p.trian.a, p -
		primitive->p.trian.a));
	else if (i == 2)
		return (vecros(primitive->p.trian.c - primitive->p.trian.b, p -
		primitive->p.trian.b));
	else if (i == 3)
		return (vecros(primitive->p.trian.a - primitive->p.trian.c, p -
		primitive->p.trian.c));
}

float		intersect_trian(t_primitive *primitive, t_ray *ray)
{
	t_vector	c[3];
	t_roots		t;
	float		test[4];

	position_tri(primitive);
	c[0] = normalize(primitive->p.trian.normal);
	if ((test[0] = dotproduct(c[0], ray->direction)) < 1e-8)
		return (INFINITY);
	test[2] = fabs((dotproduct(c[0], ray->position) + dotproduct(c[0],
		primitive->p.trian.a)) / test[0]);
	if (test[2] < 0)
		return (INFINITY);
	c[1] = ray->position + mult_vector(ray->direction, test[2]);
	c[2] = vect(primitive, c[1], 1);
	if ((test[2] = dotproduct(c[0], c[2])) < 0)
		return (INFINITY);
	c[2] = vect(primitive, c[1], 2);
	if ((test[1] = dotproduct(c[0], c[2])) < 0)
		return (INFINITY);
	c[2] = vect(primitive, c[1], 3);
	if ((test[2] = dotproduct(c[0], c[2])) < 0)
		return (INFINITY);
	t[0] = test[1] / dotproduct(c[0], c[0]);
	t[1] = test[2] / dotproduct(c[0], c[0]);
	return ((t[0] > 0) ? t[0] : t[1]);
}

float		intersect_box(t_primitive *primitive, t_ray *ray)
{
	t_vector	dirfrac;
	float		t[6];
	t_roots		t1;

	position_box(primitive);
	dirfrac[0] = (1 / ray->direction[0]);
	dirfrac[1] = (1 / ray->direction[1]);
	dirfrac[2] = (1 / ray->direction[2]);
	t[0] = (primitive->p.box.a[0] - ray->position[0]) * dirfrac[0];
	t[1] = (primitive->p.box.b[0] - ray->position[0]) * dirfrac[0];
	t[2] = (primitive->p.box.a[1] - ray->position[1]) * dirfrac[1];
	t[3] = (primitive->p.box.b[1] - ray->position[1]) * dirfrac[1];
	t[4] = (primitive->p.box.a[2] - ray->position[2]) * dirfrac[2];
	t[5] = (primitive->p.box.b[2] - ray->position[2]) * dirfrac[2];
	t1[0] = max(max(min(min(t[0], t[1]), INFINITY), min(min(t[2], t[3]),
		INFINITY)), min(min(t[4], t[5]), INFINITY));
	t1[1] = min(min(max(max(t[0], t[1]), -INFINITY), max(max(t[2], t[3]),
		-INFINITY)), max(max(t[4], t[5]), -INFINITY));
	if (t1[1] < 1e-8 || t1[0] >= t1[1] || t1[0] < 1e-8)
		return (INFINITY);
	return ((t1[0] >= 0) ? t1[0] : t1[1]);
}
