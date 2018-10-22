/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezruch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 15:21:49 by dbezruch          #+#    #+#             */
/*   Updated: 2018/09/25 15:21:52 by dbezruch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_vector	mult_vector(t_vector vector, float value)
{
	return ((t_vector){value * vector[0], value * vector[1],
					value * vector[2]});
}

float		calc_magnitude(t_vector *p)
{
	return (sqrtf((*p)[0] * (*p)[0] + (*p)[1] * (*p)[1] + (*p)[2] * (*p)[2]));
}

t_vector	normalize(t_vector p)
{
	float		a;

	a = calc_magnitude(&p);
	if (a == 0)
		return (p);
	return ((t_vector){(p[0]) / a, (p[1]) / a, (p[2]) / a});
}

float		dotproduct(t_vector p1, t_vector p2)
{
	return (p1[0] * p2[0] + p1[1] * p2[1] + p1[2] * p2[2]);
}

float		calc_distance(t_vector p1, t_vector p2)
{
	float a;
	float b;
	float c;

	a = p1[0] - p2[0];
	b = p1[1] - p2[1];
	c = p1[2] - p2[2];
	return (sqrtf(a * a + b * b + c * c));
}
