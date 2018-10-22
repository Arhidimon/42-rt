/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezruch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 14:32:18 by dbezruch          #+#    #+#             */
/*   Updated: 2018/10/22 15:58:06 by dbezruch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# define MAX(a,b)({ __typeof__ (a) _a=(a); __typeof__ (b) _b =(b);_a>_b?_a:_b;})
# define MIN(a,b)({ __typeof__ (a) _a=(a); __typeof__ (b) _b =(b);_a<_b?_a:_b;})
# define TOGGLE(x) (x = (x==0)?1:0)

# define FOV 1.0

# define BG_COLOR 0

# define SS_SQ (app->screen.ssvalue*app->screen.ssvalue)
# define A_PR &(app->scene.primitives)

# define INT_SPH (t=intersect_sphere(current,ray))>tmin&&t<closest_t
# define INT_PL (t=intersect_plane(current,ray))>tmin&&t<closest_t
# define INT_CON (t=intersect_cone(current,ray))>tmin&&t<closest_t
# define INT_CYL (t=intersect_cylinder(current,ray))>tmin&&t<closest_t

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

# define MAX_ITERS 0

# include <math.h>
# include <unistd.h>
# include <stdint.h>
# include "../frameworks/SDL2.framework/Headers/SDL.h"
# include "../frameworks/SDL2_ttf.framework/Headers/SDL_ttf.h"

# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"

typedef float			t_vector __attribute__((vector_size(sizeof(float)*3)));
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
	CONE

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

typedef	union			u_params
{
	t_plane				plane;
	t_sphere			sphere;
	t_cylinder			cylinder;
	t_cone				cone;
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
	SDL_Window			*window;
	SDL_Renderer		*renderer;
	SDL_Texture			*maintexture;
	TTF_Font			*messagefont;
	SDL_Color			messagecolor;
	int					messagewidth;
	int					messageheight;
	int32_t				framestimes[FRAME_VALUES];
	int32_t				frametimelast;
	int32_t				framecount;
	SDL_Surface			*icon;
	t_primitive			*curobj;
	t_light				*curlobj;
	t_object_type		curobjtype;
	t_light				*curl;
	float				tempfloat;
	t_vector			tv;
	t_vector			tempvector;
}						t_app;

t_vector				rotate_0x(t_vector vector, float angle);
t_vector				rotate_0y(t_vector vector, float angle);
t_vector				rotate_0z(t_vector vector, float angle);
t_vector				rotate(t_vector rotation, t_vector vector);

float					calc_magnitude(t_vector *p);

float					computelight(t_app *app, t_vector p, t_vector n,
						t_vector v);

void					add_point_light(t_light **lights, t_vector vector,
						float intensity);
void					add_ambient_light(t_light **lights, float intensity);
void					add_directional_light(t_light **lights,
						t_vector vector, float intensity);

t_primitive				*add_sphere(t_primitive **primitives, t_vector position,
						float radius, int color);
t_primitive				*add_plane(t_primitive **primitives, t_vector position,
						t_vector normal, int color);
t_primitive				*add_cylinder(t_primitive **primitives, t_ray pnr,
						float radius,
						int color);
t_primitive				*add_cone(t_primitive **primitives, t_vector position,
						t_vector normal, int color);

float					closest_intersection(t_app *app, t_ray *ray, float tmin,
						t_primitive **object);

int						trace_ray(t_app *app, t_ray *ray, float min, int depth);

t_vector				mult_vector(t_vector vector, float value);
float					dotproduct(t_vector p1, t_vector p2);
t_vector				normalize(t_vector p);
float					calc_magnitude(t_vector *p);
t_vector				reflect_ray(t_vector r, t_vector n);
float					calc_distance(t_vector p1, t_vector p2);

int						multcolor(float value, int color);
int						sumcolor(float value, int c1, int c2);

void					render(t_app *app);

t_roots					solve_qe(float a, float b, float c);

void					ssaa(t_app *app);

void					key_handler(SDL_Scancode key_sc);
void					key_handler1(t_app *app);

void					testscene_1(t_app *app);
void					testscene_2(t_app *app);
void					testscene_3(t_app *app);
void					testscene_4(t_app *app);
void					testscene_5(t_app *app);

t_vector				*get_curobj_pos(t_app *app);
t_vector				*get_curobj_dir(t_app *app);
void					next_obj(t_app *app);
void					prev_obj(t_app *app);

void					printcontrols(void);
void					printinfo(t_app *app);
void					printinfoheader(void);
void					clearinfo(void);
t_app					*initialize_app(void);
int						handle_sdl_error(void);
int						initialize_sdl(t_app *app);
int						count_fps(t_app *app);
int						print_fps(t_app *app, float fps);

#endif
