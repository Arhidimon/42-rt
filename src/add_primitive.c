/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_primitive.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezruch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 15:54:47 by dbezruch          #+#    #+#             */
/*   Updated: 2018/09/25 15:54:49 by dbezruch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_primitive	*add_primitive(t_primitive **primitives)
{
	t_primitive *primitive;
	t_primitive *temp;

	if (!primitives)
		return (NULL);
	if (!*primitives)
	{
		primitive = malloc(sizeof(t_primitive));
		primitive->prev = NULL;
		primitive->next = NULL;
		*primitives = primitive;
		return (primitive);
	}
	else
	{
		temp = (*primitives);
		while (temp->next)
			temp = temp->next;
		temp->next = malloc(sizeof(t_primitive));
		temp->next->prev = temp;
		temp->next->next = NULL;
		return (temp->next);
	}
}

t_primitive	*add_sphere(t_primitive **primitives, t_vector position,
		float radius, int color)
{
	t_primitive *primitive;

	primitive = add_primitive(primitives);
	primitive->rotation = (t_vector){0, 0, 0};
	primitive->type = SPHERE;
	primitive->p.sphere.position = position;
	primitive->p.sphere.radius = radius;
	primitive->p.sphere.radius2 = radius * radius;
	primitive->reflection = 0.0;
	primitive->specular = -1;
	primitive->color = color;
	return (primitive);
}

t_primitive	*add_cylinder(t_primitive **primitives, t_ray pnr, float radius,
		int color)
{
	t_primitive *primitive;

	primitive = add_primitive(primitives);
	primitive->rotation = (t_vector){0, 1, 0};
	primitive->type = CYLINDER;
	primitive->p.cylinder.position = pnr.position;
	primitive->p.cylinder.normal = pnr.direction;
	primitive->p.cylinder.radius = radius;
	primitive->p.cylinder.radius2 = radius * radius;
	primitive->reflection = 0.0;
	primitive->specular = -1;
	primitive->color = color;
	return (primitive);
}

t_primitive	*add_cone(t_primitive **primitives, t_vector position,
		t_vector normal, int color)
{
	t_primitive *primitive;

	primitive = add_primitive(primitives);
	primitive->rotation = (t_vector){0, 1, 0};
	primitive->type = CONE;
	primitive->p.cone.position = position;
	primitive->p.cone.normal = normal;
	primitive->p.cone.angle = 0.785;
	primitive->reflection = 0.0;
	primitive->specular = -1;
	primitive->color = color;
	return (primitive);
}

t_primitive	*add_plane(t_primitive **primitives, t_vector position,
		t_vector normal, int color)
{
	t_primitive *primitive;

	primitive = add_primitive(primitives);
	primitive->rotation = (t_vector){0, 0, 0};
	primitive->type = PLANE;
	primitive->p.plane.position = position;
	primitive->p.plane.normal = normal;
	primitive->reflection = 0.0;
	primitive->specular = -1;
	primitive->color = color;
	return (primitive);
}
