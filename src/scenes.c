/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scenes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezruch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 13:30:32 by dbezruch          #+#    #+#             */
/*   Updated: 2018/09/30 13:30:34 by dbezruch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	testscene_1(t_app *app)
{
	t_primitive *p;

	app->scene.primitives = NULL;
	app->scene.lights = NULL;
	p = add_plane(A_PR, (t_vector) {-8, 0, 0}, (t_vector) {1, 0, 0}, 0xFF00FF);
	p->reflection = 0.99;
	p = add_plane(A_PR, (t_vector) {8, 0, 0}, (t_vector) {-1, 0, 0}, 0xFF00FF);
	p->reflection = 0.99;
	p = add_plane(A_PR, (t_vector) {0, -8, 0}, (t_vector) {0, 1, 0}, 0xFF00FF);
	p->reflection = 0.99;
	p = add_plane(A_PR, (t_vector) {0, 8, 0}, (t_vector) {0, -1, 0}, 0xFF00FF);
	p->specular = -1;
	p->reflection = 0.99;
	p = add_plane(A_PR, (t_vector) {0, 0, 8}, (t_vector) {0, 0, -1}, 0xFF00FF);
	p->reflection = 0.99;
	p = add_plane(A_PR, (t_vector) {0, 0, -8}, (t_vector) {0, 0, 1}, 0xFF00FF);
	p->specular = -1;
	p->reflection = 0.99;
	p = add_sphere(A_PR, (t_vector) {0, 0, 0}, 1, 255);
	p->reflection = 0;
	p->specular = 10;
	add_ambient_light(&(app->scene.lights), 0.4);
	add_point_light(&(app->scene.lights), (t_vector) {5, 5, 0}, 0.4);
}

void	testscene_2(t_app *app)
{
	t_primitive *p;

	app->scene.primitives = NULL;
	app->scene.lights = NULL;
	p = add_plane(A_PR, (t_vector) {-8, 0, 0}, (t_vector) {1, 0, 0}, 0xFF00FF);
	p->reflection = 0.2;
	p = add_plane(A_PR, (t_vector) {8, 0, 0}, (t_vector) {-1, 0, 0}, 0xFF00FF);
	p->reflection = 0.2;
	p = add_plane(A_PR, (t_vector) {0, -8, 0}, (t_vector) {0, 1, 0}, 0xFF00FF);
	p->reflection = 0.2;
	p = add_plane(A_PR, (t_vector) {0, 8, 0}, (t_vector) {0, -1, 0}, 0xFF00FF);
	p->reflection = 0.2;
	p = add_plane(A_PR, (t_vector) {0, 0, 8}, (t_vector) {0, 0, -1}, 0xFF00FF);
	p->reflection = 0.2;
	p = add_plane(A_PR, (t_vector) {0, 0, -8}, (t_vector) {0, 0, 1}, 0xFF00FF);
	p->reflection = 0.2;
	p = add_cylinder(A_PR, (t_ray){{0, 0, 0}, {0, 1, 0}}, 1, 255);
	p->reflection = 0;
	p->specular = 10;
	add_ambient_light(&(app->scene.lights), 0.4);
	add_point_light(&(app->scene.lights), (t_vector) {5, 5, 0}, 0.4);
}

void	testscene_3(t_app *app)
{
	t_primitive *p;

	app->scene.primitives = NULL;
	app->scene.lights = NULL;
	p = add_plane(A_PR, (t_vector) {-8, 0, 0}, (t_vector) {1, 0, 0}, 0xFF00FF);
	p->reflection = 0.2;
	p = add_plane(A_PR, (t_vector) {8, 0, 0}, (t_vector) {-1, 0, 0}, 0xFF00FF);
	p->reflection = 0.2;
	p = add_plane(A_PR, (t_vector) {0, -8, 0}, (t_vector) {0, 1, 0}, 0xFF00FF);
	p->reflection = 0.2;
	p = add_plane(A_PR, (t_vector) {0, 8, 0}, (t_vector) {0, -1, 0}, 0xFF00FF);
	p->reflection = 0.2;
	p = add_plane(A_PR, (t_vector) {0, 0, 8}, (t_vector) {0, 0, -1}, 0xFF00FF);
	p->reflection = 0.2;
	p = add_plane(A_PR, (t_vector) {0, 0, -8}, (t_vector) {0, 0, 1}, 0xFF00FF);
	p->reflection = 0.2;
	p = add_cylinder(A_PR, (t_ray){{0, 0, 0}, {0, 1, 0}}, 1, 255);
	p->reflection = 0;
	p->specular = 10;
	add_point_light(&(app->scene.lights), (t_vector) {5, 0, 1}, 0.4);
	p = add_cone(A_PR, (t_vector) {0, 1, 0}, (t_vector) {0, 1, 0}, 255);
	p->reflection = 0.0;
	p->specular = 10;
	add_ambient_light(&(app->scene.lights), 0.4);
}

void	testscene_4(t_app *app)
{
	t_primitive *p;

	app->scene.primitives = NULL;
	app->scene.lights = NULL;
	add_point_light(&(app->scene.lights), (t_vector) {5, 0, 0}, 0.4);
	add_point_light(&(app->scene.lights), (t_vector) {-5, 5, -5}, 0.4);
	p = add_sphere(&(app->scene.primitives), (t_vector) {0, -1, 3}, 1, 255);
	p->reflection = 0.0;
	p->specular = 1;
	p = add_sphere(A_PR, (t_vector) {2, 0, 4}, 1, 255 << 8);
	p->reflection = 0.0;
	p->specular = 50;
	p = add_sphere(A_PR, (t_vector) {-2, 0, 4}, 1, 255 << 16);
	p->reflection = 0.0;
	p->specular = 100;
	p = add_plane(A_PR, (t_vector) {0, -2, 0},
			(t_vector) {0, 1, 0}, 0xFF00FF);
	p->reflection = 0.5;
	p->specular = 1;
	add_ambient_light(&(app->scene.lights), 0.4);
	p->specular = -1;
	p->reflection = 0.5;
}

void	testscene_5(t_app *app)
{
	app->scene.primitives = NULL;
	app->scene.lights = NULL;
	add_point_light(&(app->scene.lights), (t_vector) {5, 0, 0}, 0.4);
	add_ambient_light(&(app->scene.lights), 0.4);
}
