/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezruch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 15:53:03 by dbezruch          #+#    #+#             */
/*   Updated: 2019/01/17 19:36:38 by atikhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_roots		solve_qe(float a, float b, float c)
{
	float		d;
	float		sqrtd;

	d = b * b - 4 * a * c;
	if (d >= 0)
	{
		if (d == 0)
		{
			d = -b / (2 * a);
			return ((t_roots){d, d});
		}
		else
		{
			sqrtd = sqrtf(d);
			return ((t_roots){(-b - sqrtd) / (2 * a), (-b + sqrtd) / (2 * a)});
		}
	}
	else
		return ((t_roots){NAN, NAN});
}

float		max(float x, float y)
{
	if (x > y)
		return (x);
	return (y);
}

float		min(float x, float y)
{
	if (x < y)
		return (x);
	return (y);
}

t_vector	vecros(t_vector a, t_vector b)
{
	t_vector resss;

	resss = (t_vector)
		{a[1] * b[2] - a[2] * b[1], a[1] * b[0] - a[0] * b[2], a[0] *
		b[1] - a[1] * b[0]};
	return (resss);
}
