/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezruch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 14:32:18 by dbezruch          #+#    #+#             */
/*   Updated: 2019/01/17 19:17:09 by atikhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# define TOGGLE(x) (x = (x==0)?1:0)

# define FOV 1.0

# define BG_COLOR 0

# define SS_SQ (g_app->screen.ssvalue*g_app->screen.ssvalue)
# define A_PR &(g_app->scene.primitives)

# define INT_SPH (t=intersect_sphere(current,ray))>tmin&&t<closest_t
# define INT_PL (t=intersect_plane(current,ray))>tmin&&t<closest_t
# define INT_CON (t=intersect_cone(current,ray))>tmin&&t<closest_t
# define INT_CYL (t=intersect_cylinder(current,ray))>tmin&&t<closest_t
# define INT_TRI (t=intersect_trian(current,ray))>tmin&&t<closest_t
# define INT_BOX (t=intersect_box(current,ray))>tmin&&t<closest_t

# define TM1 ray->direction,mult_vector(closest_obj->rotation,closest_t)
# define TC1 ray->position-closest_obj->p.cylinder.position
# define TC2 ray->position-closest_obj->p.cone.position
# define TEMP_M (dotproduct(TM1)+dotproduct(closest_obj->rotation,TC1))
# define TEMP_M1 (dotproduct(TM1)+dotproduct(closest_obj->rotation,TC2))

# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 640
# define FRAME_VALUES 60
# define SS_VALUE 1
# define SC_WH SCREEN_WIDTH,SCREEN_HEIGHT

# define VIEWPORT_WIDTH 1
# define VIEWPORT_HEIGHT 1

# define CAMERA_MOVE 0.25
# define CAMERA_ROTATE 0.1

# define KEY_NONE 0

# define FONT_SIZE 50

# define MAX_ITERS 10

# include <math.h>
# include <unistd.h>
# include <stdint.h>
# include <stdlib.h>
# include <gtk/gtk.h>

typedef float			t_vector __attribute__((vector_size(sizeof(float)*4)));
typedef float			t_roots __attribute__((vector_size(sizeof(float)*2)));

typedef struct			s_vertex
{
	t_vector			vector;
	int					color;
}						t_vertex;

typedef enum			e_primitive_type
{
	UNDEFINED,
	PLANE,
	SPHERE,
	CYLINDER,
	CONE,
	TRIAN,
	BOX
}						t_primitive_type;

typedef enum			e_object_type
{
	LIGHT = 0,
	PRIMITIVE = 1,
	CAMERA = 2
}						t_object_type;

typedef enum			e_light_type
{
	POINT,
	AMBIENT,
	DIRECTIONAL
}						t_light_type;

typedef struct			s_sphere
{
	t_vector			position;
	float				radius;
	float				radius2;
}						t_sphere;

typedef struct			s_plane
{
	t_vector			position;
	t_vector			normal;
}						t_plane;

typedef struct			s_cylinder
{
	t_vector			position;
	t_vector			normal;
	float				radius;
	float				radius2;
}						t_cylinder;

typedef struct			s_cone
{
	t_vector			position;
	t_vector			normal;
	float				angle;
}						t_cone;

typedef struct			s_trian
{
	t_vector			position;
	t_vector			a;
	t_vector			b;
	t_vector			c;
	t_vector			a1;
	t_vector			b1;
	t_vector			c1;
	t_vector			normal;
	float				radius;
	float				radius2;
}						t_trian;

typedef struct			s_box
{
	t_vector			position;
	t_vector			a;
	t_vector			b;
	float				radius;
	float				radius2;
}						t_box;

typedef	union			u_params
{
	t_plane				plane;
	t_sphere			sphere;
	t_cylinder			cylinder;
	t_cone				cone;
	t_trian				trian;
	t_box				box;
}						t_params;

typedef struct			s_primitive
{
	t_vector			position;
	t_primitive_type	type;
	t_params			p;
	float				transparency;
	float				reflection;
	int					specular;
	int					color;
	t_vector			rotation;
	struct s_primitive	*prev;
	struct s_primitive	*next;

}						t_primitive;

typedef struct			s_ray
{
	t_vector			position;
	t_vector			direction;
}						t_ray;

typedef struct			s_camera
{
	t_vector			position;
	t_vector			direction;
	float				fov;
	float				a;
	float				b;
	float				g;
}						t_camera;

typedef struct			s_light
{
	t_light_type		type;
	float				intensity;
	t_vector			vector;
	struct s_light		*next;
	struct s_light		*prev;
}						t_light;

typedef struct			s_scene
{
	t_ray				*rays;
	t_light				*lights;
	t_primitive			*primitives;

}						t_scene;

typedef struct			s_screen
{
	int					width;
	int					height;
	int					ssvalue;
	int32_t				*pixels;
	int32_t				*sspixels;
}						t_screen;

typedef struct			s_app
{
	size_t				iterations;
	unsigned char		shadow;
	unsigned char		light;
	t_camera			camera;
	t_scene				scene;
	t_screen			screen;
	t_primitive			*curobj;
	t_light				*curlobj;
	t_object_type		curobjtype;
	t_light				*curl;
	float				tempfloat;
	t_vector			tv;
	t_vector			tempvector;

	GtkWidget			*progressbar;
	GtkWidget			*window;
	GtkWidget			*da;
	GtkWidget			*opendialog;
	GtkBuilder			*builder;
}						t_app;

extern t_app *g_app;
extern char g_stoprendering;

t_vector				rotate_0x(t_vector vector, float angle);
t_vector				rotate_0y(t_vector vector, float angle);
t_vector				rotate_0z(t_vector vector, float angle);
t_vector				rotate(t_vector rotation, t_vector vector);
t_vector				vecros(t_vector a, t_vector b);
t_vector				get_normal_trian(t_primitive *primitive);
t_vector				vecros(t_vector a, t_vector b);
t_primitive				*add_primitive(t_primitive **primitives);

float					calc_magnitude(t_vector *p);

float					computelight(t_vector p, t_vector n,
						t_vector v);

void					add_point_light(t_light **lights, t_vector vector,
						float intensity);
void					add_ambient_light(t_light **lights, float intensity);
void					add_directional_light(t_light **lights,
						t_vector vector, float intensity);
float					max(float x, float y);
float					min(float x, float y);

t_primitive				*add_sphere(t_primitive **primitives, t_vector position,
						float radius, int color);
t_primitive				*add_plane(t_primitive **primitives, t_vector position,
						t_vector normal, int color);
t_primitive				*add_cylinder(t_primitive **primitives, t_ray pnr,
						float radius,
						int color);
t_primitive				*add_cone(t_primitive **primitives, t_vector position,
						t_vector normal, int color);
t_primitive				*add_trian(t_primitive **primitives, t_vector position, t_vector normal,
						float radius, int color);
t_primitive				*add_box(t_primitive **primitives, t_vector position,
						float radius, int color);
t_primitive				*add_trian(t_primitive **primitives, t_vector position,
						t_vector normal, float radius, int color);
t_primitive				*add_box(t_primitive **primitives, t_vector position,
						float radius, int color);

float					closest_intersection(t_ray *ray, float tmin,
						t_primitive **object);
float					intersect_box(t_primitive *primitive, t_ray *ray);
float					intersect_trian(t_primitive *primitive, t_ray *ray);

int						trace_ray(t_ray *ray, float min, int depth);

t_vector				mult_vector(t_vector vector, float value);
float					dotproduct(t_vector p1, t_vector p2);
t_vector				normalize(t_vector p);
float					calc_magnitude(t_vector *p);
t_vector				reflect_ray(t_vector r, t_vector n);
float					calc_distance(t_vector p1, t_vector p2);

int						multcolor(float value, int color);
int						sumcolor(float value, int c1, int c2);

void					render(void);

t_roots					solve_qe(float a, float b, float c);

void					ssaa(void);

void					key_handler1(void);

void					testscene_1(void);
void					testscene_2(void);
void					testscene_3(void);
void					testscene_4(void);
void					testscene_5(void);

t_vector				*get_curobj_pos(void);
t_vector				*get_curobj_dir(void);
void					next_obj(void);
void					prev_obj(void);

void					printcontrols(void);
void					printinfo(void);
void					printinfoheader(void);
void					clearinfo(void);
void					initialize_app(void);
int						handle_sdl_error(void);
void					initialize_gtk(void);
int						count_fps(void);
int						print_fps(float fps);

void					free_scene();

char					*ft_parser(char *filepath);

#endif
