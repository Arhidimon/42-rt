/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezruch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 15:53:03 by dbezruch          #+#    #+#             */
/*   Updated: 2018/09/25 15:53:05 by dbezruch         ###   ########.fr       */
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
