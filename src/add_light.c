/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_light.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezruch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 15:09:25 by dbezruch          #+#    #+#             */
/*   Updated: 2018/09/25 15:11:36 by dbezruch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_light	*add_light(t_light **lights)
{
	t_light *light;
	t_light *temp;

	if (!lights)
		return (NULL);
	if (!*lights)
	{
		light = malloc(sizeof(t_light));
		light->next = NULL;
		light->prev = NULL;
		*lights = light;
		return (light);
	}
	else
	{
		temp = (*lights);
		while (temp->next)
			temp = temp->next;
		temp->next = malloc(sizeof(t_light));
		temp->next->prev = temp;
		temp->next->next = NULL;
		return (temp->next);
	}
}

void	add_point_light(t_light **lights, t_vector vector, float intensity)
{
	t_light *light;

	light = add_light(lights);
	light->type = POINT;
	light->intensity = intensity;
	light->vector = vector;
}

void	add_directional_light(t_light **lights, t_vector vector,
		float intensity)
{
	t_light *light;

	light = add_light(lights);
	light->type = DIRECTIONAL;
	light->intensity = intensity;
	light->vector = vector;
}

void	add_ambient_light(t_light **lights, float intensity)
{
	t_light *light;

	light = add_light(lights);
	light->type = AMBIENT;
	light->intensity = intensity;
}
