/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Helene <Helene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 00:04:46 by hlesny            #+#    #+#             */
/*   Updated: 2023/11/22 16:46:41 by Helene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/struct.h"
#include "../../inc/mini_rt.h"

/* ------------------------- UTILS ---------------------------- */


/* ------- POINTS -------- */

t_point_3d	point_double_multiply(double n, t_point_3d a)
{
	t_point_3d b;

	b.x = n * a.x;
	b.y = n * a.y;
	b.z = n * a.z;
	return (b);
}

t_point_3d	point_addition(t_point_3d a, t_point_3d b)
{
	t_point_3d c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	return (c);
}

t_point_3d	point_substract(t_point_3d a, t_point_3d b)
{
	return (point_addition(a, point_double_multiply(-1, b)));
}

/* ------- VECTORS -------- */

/* utile pour le ray traversal algorithm, dans lequel somme points et vecteurs */
t_point_3d	get_vec_coord(t_vec_3d v)
{
	t_point_3d p;

	p.x = v.x;
	p.y = v.y;
	p.z = v.z;
	return (p);
}

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




/* ---------------------- NORMALS COMPUTATIONS ----------------------- */

/* need center coordinates */
t_vec_3d	normal_to_sphere(void *obj, t_point_3d p)
{
	t_sphere *sp;

	sp = obj;
	
}

/* produit vectoriel de deux vecteurs generateurs du plan */
t_vec_3d	normal_to_plan(void *obj, t_point_3d p)
{
	t_plan *pl;

	pl = obj;
}

/* traduit en coord cylindriques, calcule la normale, puis reconvertit en 
coord cartesiennes (?) */
t_vec_3d 	normal_to_cylinder(void *obj, t_point_3d p)
{
	t_cylindre	*cyl;

	cyl = obj;
}

t_vec_3d	normal_to_cone(void *obj, t_point_3d p)
{
	t_cone *cn;

	cn = obj;	
}

/* computes the normal of a point p on a given object */
t_vec_3d get_unit_normal(t_hit_info hi, t_point_3d p)
{
	t_vec_3d normal;

	if (hi.obj_type == sphere)
		normal = normal_to_sphere(hi.obj_content, p);
	else if (hi.obj_type == plan)
		normal = normal_to_plan(hi.obj_content, p);
	else if (hi.obj_type == cylindre)
		normal = normal_to_cylinder(hi.obj_content, p);
	else if (hi.obj_type == cone)
		normal = normal_to_cone(hi.obj_content, p);
	else
		;// ?
	
	normalise(&normal);
	return (normal);
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

/* ------ RAY - OBJECTS INTERSECTIONS ----- */

/* get the corresponding bsp_node.
check for intersections ray - objects in the current and children nodes */
t_hit_info closest_intersection(t_ray ray)
{
	t_bsp_node *start;
	t_hit_info h_inf;
	
	start = get_corresponding_node(ray);


	/* ray.p_normal = get_unit_normal(ray.hit_info, ray.intersect_point);
	normalise(&ray.p_normal); */
	return (h_inf);
}

/* ------------- LIGHT -------------- */

/* matte objects */
double	diffuse_reflection(t_light *lights, t_ray ray)
{
	double 		intensity;
	double		n_dot_l;
	t_vec_3d	light_direction;
	t_hit_info	closest_hit;
	t_light 	*curr;

	curr = lights;
	intensity = 0;
	while (curr)
	{
		// détermine si l'objet est éclairé par la source lumineuse
		closest_hit = closest_intersection(ray);
		if (closest_hit.distance != -1) // set a -1 si le rayon n'intersecte pas d'objets
		{
			light_direction = get_directional_vect(ray.hit_info.hit_point, curr->p);
			n_dot_l = vec_x_vec_scal(ray.hit_info.hit_p_normal, light_direction);
			if (n_dot_l > 0)
				intensity += curr->infos.ratio * n_dot_l/(ray.hit_info.hit_p_normal.norm * light_direction.norm);
		}
		curr = curr->next;
	}
	return (intensity);
}

t_vec_3d get_incident_ray_of_light(t_vec_3d l, t_vec_3d n)
{
	return (vect_substract(vect_double_multiply(2, vect_double_multiply(vec_x_vec_scal(n, l), n)), l));
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
double 	specular_reflection(t_light *lights, double s_term, t_ray ray)
{
	double 		intensity;
	t_vec_3d	light_direction;
	t_vec_3d	r;
	t_hit_info	closest_hit;
	t_light 	*curr;

	curr = lights;
	intensity = 0;
	while (curr)
	{
		// détermine si l'objet est éclairé par la source lumineuse
		closest_hit = closest_intersection(ray);
		if (closest_hit.distance != -1)
		{
			light_direction = get_directional_vect(ray.hit_info.hit_point, curr->p);
			r = get_incident_ray_of_light(light_direction, ray.hit_info.hit_p_normal);
			if (vec_x_vec_scal(r, ray.hit_info.reflected_ray) > 0)
			{
				intensity += curr->infos.ratio * pow((vec_x_vec_scal(r, ray.hit_info.reflected_ray) 
					/ (r.norm * ray.hit_info.reflected_ray.norm)), s_term);	
			}
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
/* compute the received light (diffuse + specular + mood light) 
	-> use the total light intensity's computing formula */
double 	compute_lighting(t_parsing_data pdata, t_vlist *object, t_ray ray) 
{
	double		intensity;

	intensity = pdata.mooooo->infos.ratio;
	intensity += diffuse_reflection(pdata.lights, ray);
	if (object->material.specular != -1)
		intensity += specular_reflection(pdata.lights, object->material.specular, ray);
	return (intensity);
}

/* ---------------------------*/

t_ray	set_ray_infos(t_vec_3d direction, t_point_3d ray_origin)
{
	t_ray ray;
	ft_memset(&ray, 0, sizeof(t_ray));

	ray.origin = ray_origin;
	ray.direction = direction;	
}

int    trace_ray(t_app app, t_point_3d ray_origin, t_vec_3d dir, int rebound_nb)
{
    t_ray		ray;
	t_vec_3d	reflected_ray;
	double 		local_color;
	double 		reflected_color;
	
	/* ray.origin = ray_origin;
	ray.direction = get_unitary_dir_vect(ray.origin, intersect_point); */
	set_ray_infos(dir, ray_origin);
	
	/* determine the closest intersection point's reflective ray's  direction */
	ray.hit_info = closest_intersection(ray);
	if (ray.hit_info.distance == -1)
		return (BACKGROUND_COLOR); 
	
	// a mettre directement dans closest_intersection()
	ray.hit_info.hit_p_normal = get_unit_normal(ray.hit_info, ray.hit_info.hit_point);
	ray.hit_info.reflected_ray = get_directional_vect(ray.hit_info.hit_point, ray.origin); // essayer avec -ray.direction et voir si donne les memes resultats
	
	local_color = ray.hit_info.obj_mat.color * compute_lighting(app.p_data, app.p_data.objects, ray);
	
	/* get the final pixel's color */
	if (ray.hit_info.obj_mat.reflective <= 0 || rebound_nb == RECURS_LIMIT)
		return (local_color);

	/* compute reflected color */
	reflected_ray = get_incident_ray_of_light(ray.direction, ray.hit_info.hit_p_normal); // ?
	reflected_color = trace_ray(app, ray.hit_info.hit_point, reflected_ray, rebound_nb + 1);
	
	return (local_color * (1 - ray.hit_info.obj_mat.reflective) + reflected_color * ray.hit_info.obj_mat.reflective);
}

int		get_final_pixel_color(t_app app, int x, int y)
{
	int	pixel_color;
	
	t_point_3d	viewp = pixel_to_viewpoint_coord(x, y);
    pixel_color = trace_ray(app, app.p_data.cam->p, get_directional_vect(app.p_data.cam->p, viewp), 0);
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
			img_pixel_put(app.mlx_data.image, x, y, get_final_pixel_color(app, x, y));
			x++;
		}
		y++;
	}
}
