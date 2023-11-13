/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 00:04:46 by hlesny            #+#    #+#             */
/*   Updated: 2023/11/13 15:42:37 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/struct.h"
#include "../../inc/mini_rt.h"

# define RECURS_LIMIT	3

typedef struct	s_hit_info
{
	// autre chose ?
	t_raytracing_material	obj_mat;
	t_point_3d				hit_point;
	double					distance; // ray_origin - object distance
}				t_hit_info;

typedef struct	s_ray
{
	t_point_3d	origin;
	t_vec_3d	direction;
}				t_ray;

/* ------------------------- UTILS ---------------------------- */

t_vec_3d	vect_double_multiply(double n, t_vec_3d a)
{
	t_vec_3d b;

	b.x = n * a.x;
	b.y = n * a.y;
	b.z = n * a.z;
	b.norm = get_v_norm(b);
	return (b);
}

t_vec_3d	vect_addition(t_vec_3d a, t_vec_3d b)
{
	t_vec_3d c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	c.norm = get_v_norm(c);
	return (c);
}

t_vec_3d	vect_substract(t_vec_3d a, t_vec_3d b)
{
	return (vect_addition(a, vect_double_multiply(-1, b)));
}

/* computes the normal of a point p on a given object */
t_vec_3d get_normal(t_vlist *object, t_point_3d p)
{
	t_vec_3d normal;

	(void)object;

	return (normal);
}

void    normalise(t_vec_3d *v)
{
    v->x /= v->norm;
    v->y /= v->norm;
    v->z /= v->norm;
    v->norm = 1;
}

t_vec_3d	get_directional_vect(t_point_3d a, t_point_3d b)
{
    t_vec_3d u;

    u.x = b.x - a.x;
    u.y = b.y - a.y;
    u.z = b.z - a.z;
    u.norm = sqrt(pow(u.x, 2) + pow(u.y, 2) + pow(u.z, 2));
    return (u);
}

t_vec_3d	get_unitary_dir_vect(t_point_3d a, t_point_3d b)
{
	t_vec_3d u;

	u = get_directional_vect(a, b);
	normalise(&u);
	return (u);
}

/* ------------------ SCREEN - SCENE CONVERTIONS UTILS --------------- */

// tej les 3 une fois qu'a les singletons, juste pr que ca compile
# define DIST 1
# define VWP_H 1
# define VWP_W 1

/* Computes the height and width of the viewpoint, 
according to the field of view (FOV) parameter and the distance (arbitrary) */
void 	get_viewpoint_dimensions(float fov)
{
	double 	viewpoint_width;
	double	viewpoint_height;

    viewpoint_width = FOCUS_DIST * tan(fov * 0.5f * DEG_TO_RAD) * 2; /* Width */
    viewpoint_height = viewpoint_width * SCREEN_RATIO; /* Height */

    // set the viewpoint's height and width singletons 
}

/* Computes the position of the current pixel on the 
camera's projection plane (ie viewpoint) */
t_point_3d pixel_to_viewpoint_coord(int x, int y)
{
    t_point_3d v;

    v.x = VWP_W * (x / SCREEN_WIDTH);
    v.y = VWP_H * (y / SCREEN_HEIGHT);
    v.z = DIST;
    return (v);
}

/* canvas = centre au milieu (et non pas (0,0) en haut a gauche de l'ecran) */
t_point_2d  pixel_to_screen(t_point_2d c)
{
    t_point_2d s;

    s.x = SCREEN_WIDTH / 2 + c.x;
    s.y = SCREEN_HEIGHT / 2 - c.y;
    return (s);
}

/*  ---------------------- MAIN FUNCTIONS -------------------------- */

int 	get_pixel_color()
{
	
}

/* ------ RAY - OBJECTS INTERSECTIONS ----- */

t_bsp_node	*get_corresponding_node()
{
	t_bsp_node *curr;

	return (curr);
}

/* get the corresponding bsp_node.
check for intersections ray - objects in the current and children nodes */
t_hit_info closest_intersection()
{
	// t_bsp_node *start = get_corresponding_node(t_ray ray);
	
	t_hit_info h_inf;


	return (t_hit_info);
}

/* ------------- LIGHT -------------- */

/* matte objects */
double	diffuse_reflection_term(t_light *lights, t_point_3d p, t_vec_3d p_normal)
{
	double 		intensity;
	double		n_dot_l;
	t_vec_3d	direction;
	t_hit_info	closest_hit;
	t_light 	*curr;

	curr = lights;
	intensity = 0;
	while (curr)
	{
		// if curr->specular ==
		closest_hit = closest_intersection();
		// détermine si l'objet est éclairé par la source lumineuse
		if (closest_hit.distance != -1) // set a -1 si le rayon n'intersecte pas d'objets
		{
			direction = get_directional_vect(curr->p - p);
			n_dot_l = prod_vec(p_normal, direction);
			if (n_dot_l > 0)
				intensity += curr->ratio * n_dot_l/(p_normal.norm * direction.norm);
		}
		curr = curr->next;
	}
	return (intensity);
}

t_vec_3d get_incident_ray_of_light(t_vec_3d l, t_vec_3d n)
{
	return (vect_substract(vect_double_multiply(2, vect_double_multiply(n, vec_x_vec_scal(n, l))), l));
}

/* shiny objects 
Unlike matte objects, shiny objects look slightly different depending 
on where you’re looking from. 

As with diffuse lighting, it’s possible that cos(α) is negative, 
and we should ignore it for the same reason as before.
Also, not every object has to be shiny; for matte objects, 
the specular term shouldn’t be computed at all.
We’ll note this in the scene by setting their specular exponent to −1 
and handling them accordingly.

*/
double 	specular_reflection_term(t_light *lights, t_point_3d p, t_vec_3d v, t_vec_3d p_normal)
{
	double 		intensity;
	t_vec_3d	direction;
	t_vec_3d	r;
	t_hit_info	closest_hit;
	t_light 	*curr;

	curr = lights;
	intensity = 0;
	while (curr)
	{
		closest_hit = closest_intersection();
		if (closest_hit.distance != -1) // détermine si l'objet est éclairé par la source lumineuse
		{
			direction = get_directional_vect(curr->p - p);
			r = get_incident_ray_of_light(direction, p_normal);
			intensity += curr->ratio * pow((vec_x_vec_scal(r, v) / (r.norm * v.norm), curr->specular));	
		}
		curr = curr->next;
	}
	return (intensity);
}

/* 
N  is the normal of the surface at P, V is the vector from P to the camera,
s is the specular exponent of the surface, Ii is the intensity of light i,
Li is the vector from P to light i,
and Ri is the reflection vector at P for light i.

p = point d'intersection rayon lumineux - object
origin = point de départ du rayon (avant les rebonds, la premiere origine est la camera)

Shadows : If there’s an object between the point and the light,
don’t add the illumination coming from this light

*/
double 	compute_lighting(t_lights *light, t_vlist *object, t_ray ray, t_point_3d p, t_point_3d origin) 
{
	double		intensity;
	t_vec_3d	p_normal;

	intensity = mood_light->ratio; // ou est stocké mood_light ?
	p_normal = normalise(&get_normal(object, p));
	intensity += diffuse_reflection_term(lights, p, p_normal);
	if (object->material.specular != -1)
		intensity += specular_reflection_term(lights, p, ray.direction, p_normal);
	return (intensity);
}

/* ---------------------------*/

int    trace_ray(t_app app, t_point_3d ray_origin, t_point_3d p, int rebound_nb)
{
    t_ray		ray; // pas utile
	t_hit_info	intersection;
	double 		reflected_color;
	double 		local_color;
	
	ray.origin = ray_origin;
	ray.direction = get_unitary_dir_vect(ray.origin, p);
	
	/* determine the closest intersection point's reflective ray's  direction */
	intersection = closest_intersection();
	if (intersection.distance == -1)
		return (BACKGROUND_COLOR); 
	
	/* compute the received light (diffuse + specular + mood light) 
		-> use the total light intensity's computing formula */
	
	local_color = intersection.obj_mat.color * compute_lighting(app.p_data.lights, app.p_data.objects, ray);
	
	
	/* get the final pixel's color */
	if (intersection.obj_mat.reflective <= 0 || rebound_nb == RECURS_LIMIT)
		return (local_color);

	/* compute reflected color */
	reflected_color = trace_ray(app, intersection.hit_point, , rebound_nb + 1);
	
	return (local_color * (1 - intersection.obj_mat.reflective) + reflected_color * intersection.obj_mat.reflective);
}

int		get_final_pixel_color(t_app app)
{
	int	pixel_color;
	
	t_point_3d	viewp = pixel_to_viewpoint_coord(x, y);
    pixel_color = trace_ray(app, app.p_data.cam->p, viewp, 0);
	
}

void    draw_scene(t_app app)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	// definir l'image
	while (y < WINDOWS_HEIGHT)
	{
		while (x < WINDOWS_WIDHT)
		{
			img_pixel_put(app.image, x, y, get_final_pixel_color(app, x, y));
			x++;
		}
		y++;
	}
}