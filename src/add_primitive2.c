/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_primitive2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaznodi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 18:34:23 by vkaznodi          #+#    #+#             */
/*   Updated: 2019/01/17 19:31:25 by atikhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_primitive		*add_trian(t_primitive **primitives, t_vector position,
		float radius, int color)
{
	t_primitive *primitive;

	primitive = add_primitive(primitives);
	primitive->rotation = (t_vector){0, 1, 0};
	primitive->type = TRIAN;
	primitive->p.trian.position = position;
	primitive->p.trian.normal = normal;
	primitive->p.trian.radius = radius;
	primitive->p.trian.radius2 = radius * radius;
	primitive->reflection = 0.0;
	primitive->specular = -1;
	primitive->color = color;
	return (primitive);
}

t_primitive		*add_box(t_primitive **primitives, t_vector position,
		float radius, int color)
{
	t_primitive *primitive;

	primitive = add_primitive(primitives);
	primitive->rotation = (t_vector){0, 1, 0};
	primitive->type = BOX;
	primitive->p.box.position = position;
	primitive->p.box.radius = radius;
	primitive->p.box.radius2 = radius * radius;
	primitive->reflection = 0.0;
	primitive->specular = -1;
	primitive->color = color;
	return (primitive);
}
