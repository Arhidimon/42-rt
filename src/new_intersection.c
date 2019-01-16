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

double		max(double x, double y)
{
	if (x > y)
		return (x);
	return (y);
}

double		min(double x, double y)
{
	if (x < y)
		return (x);
	return (y);
}

t_vector		vecros(t_vector a, t_vector b)
{
	t_vector resss;

	resss = (t_vector){a[1] * b[2] - a[2] * b[1], a[1] * b[0] - a[0] * b[2], a[0] *
		b[1] - a[1] * b[0]};
	return (resss);
}
t_vector		vecscale(double tmp, t_vector v1)
{
	t_vector v;

	v = (t_vector){tmp * v1[0], tmp * v1[1], tmp * v1[2]};
	return (v);
}

t_vector		vectadd(t_vector v1, t_vector v2)
{
	t_vector result;

	result = (t_vector){v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]};
	return (result);
}

float		intersect_trian(t_primitive *primitive, t_ray *ray)
{
	t_vector	v0, v1, v2, v0v1, v0v2, pvec;
    float t0, t;
	float EPSILON = 1e-8;
	v0 = (t_vector){(primitive->p.trian.position[0] - primitive->p.trian.radius),
		(primitive->p.trian.position[1] - primitive->p.trian.radius), primitive->p.trian.position[2]};
	v1 = (t_vector){(primitive->p.trian.position[0] + primitive->p.trian.radius),
		(primitive->p.trian.position[1] - primitive->p.trian.radius), primitive->p.trian.position[2]};
	v2 = (t_vector){(primitive->p.trian.position[0]), (primitive->p.trian.position[1]
		+ primitive->p.trian.radius), primitive->p.trian.position[2]};
	// v0 = (t_vector){-1, -1, -1};
	// v1 = (t_vector){1, -1, -1};
	// v2 = (t_vector){0, 1, -1};
	// c = normalize(primitive->p.trian.normal);//get_normal_trian(primitive);
	v0v1 = v1 - v0;
	v0v2 = v2 - v0;
	// c = normalize(vecros(a, b));
	pvec = vecros((ray->direction), v0v2);
	float det = ((dotproduct(v0v1, pvec)));
	// printf("%f\n", det);
	if (fabs(det) < EPSILON)
	 	return (INFINITY);
	 float invDet = 1 / det;
	 t_vector tvec = ray->position - v0;
	 float u = dotproduct(tvec, pvec) * invDet;
	 if (u < 0 || u > 1)
	 	return (INFINITY);
	 t_vector qvec = vecros(tvec, v0v1);
	 float v = (dotproduct(ray->direction, qvec)) * invDet;
	// printf("%f\n", invDet);
	 if (v < 0 || u + v > 1)
	 	return (INFINITY);
	 t = dotproduct(v0v2, qvec) * invDet;
	 return (t);
	// float denom = dotproduct(c, c);
	// float h2 = dotproduct(c, ray->direction);
	// // h2 = fabs(h2);
	// if (h2 < EPSILON )
	// 	return (INFINITY);
	// float d = dotproduct(c, v1);
	// float t1 = fabs((dotproduct(c, ray->position) + d) / h2);
	// if (t1 < 0)
	// 	return (INFINITY);
	// t_vector p = vectadd(ray->position , vecscale(t1, ray->direction));
	// t_vector edge0 = v2 - v1;
	// t_vector vp0 = p - v1;
	// t_vector c1 = vecros(edge0, vp0);
	// float test = (dotproduct(c, c1));
	// if (test < 0)
	// 	return (INFINITY);
	// t_vector edge1 = v3 - v2;
	// t_vector vp1 = p - v2;
	// c1 = vecros(edge1, vp1);
	// float test1 = dotproduct(c, c1);
	// if (test1 < 0)
	// 	return (INFINITY);
	// t_vector edge2 = v1 - v3;
	// t_vector vp2 = p - v3;
	// c1 = vecros(edge2, vp2);
	// test = dotproduct(c, c1);
	// if (test < 0)
	// 	return (INFINITY);
	// t0 = test1 / denom;
	// t = test / denom;
	// return ((t0 > 0) ? t0 : t);
}

float		intersect_box(t_primitive *primitive, t_ray *ray)
{
	t_vector dirfrac;
	t_vector	lb;
	t_vector	rt;
	float		t[6];
	t_roots		t1;
	int s[3];

	lb = (t_vector){(primitive->p.box.position[0]),
		(primitive->p.box.position[1]), primitive->p.box.position[2]};
	rt = (t_vector){(primitive->p.box.position[0] + primitive->p.box.radius2),
		(primitive->p.box.position[1] + primitive->p.box.radius2), primitive->p.box.position[2] + primitive->p.box.radius2};
	dirfrac[0] = (1 / ray->direction[0]);
	dirfrac[1] = (1 / ray->direction[1]);
	dirfrac[2] = (1 / ray->direction[2]);
	t[0] = (lb[0] - ray->position[0]) * dirfrac[0];
	t[1] = (rt[0] - ray->position[0]) * dirfrac[0];
	t[2] = (lb[1] - ray->position[1]) * dirfrac[1];
	t[3] = (rt[1] - ray->position[1]) * dirfrac[1];
	t[4] = (lb[2] - ray->position[2]) * dirfrac[2];
	t[5] = (rt[2] - ray->position[2]) * dirfrac[2];
	t1[0] = max(max(min(t[0], t[1]), min(t[2], t[3])), min(t[4], t[5]));
	t1[1] = min(min(max(t[0], t[1]), max(t[2], t[3])), max(t[4], t[5]));
	if (t1[1] < 1e-8 || t1[0] >= t1[1] || t1[0] < 1e-8)
		return (INFINITY);
	// printf("%f\n", t1[0]);
	// return ((t1[0] >= 0) ? t1[0] : t1[1]);
	// if (t1[0] > t1[1])
	// 	return (t1[1]);
	return (t1[0] >= 0);
}
