/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 18:15:45 by hlesny            #+#    #+#             */
/*   Updated: 2023/11/29 19:59:43 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/struct.h"
#include "../../inc/mini_rt.h"

/* ------------- LIGHT -------------- */

/* matte objects */
double	diffuse_reflection(t_app *app, t_ray ray)
{
	double 		intensity;
	double		n_dot_l;
	t_ray		obj_to_light; 
	t_light 	*curr;

	curr = app->p_data.lights;
	intensity = 0;
	obj_to_light.origin = ray.hit_info.hit_point;
	while (curr)
	{
		obj_to_light.direction = get_directional_vect(ray.hit_info.hit_point, curr->p);  // light_direction, aka L
		
		// détermine si l'objet est éclairé par la source lumineuse
		//ray_traversal_algo(&app->root, &obj_to_light); // mettre &obj_to_light je penseeee
		no_tree_intersections(app->p_data.objects, &obj_to_light);
		
		if (obj_to_light.hit_info.distance != -1) // set a -1 si le rayon n'intersecte pas d'objets
		{
			n_dot_l = vec_x_vec_scal(ray.hit_info.hit_p_normal, obj_to_light.direction);
			if (n_dot_l > 0)
				intensity += curr->infos.ratio * n_dot_l/(ray.hit_info.hit_p_normal.norm * obj_to_light.direction.norm);
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
double 	specular_reflection(t_app *app, double s_term, t_ray ray)
{
	double 		intensity;
	t_vec_3d	r;
	//t_hit_info	closest_hit; // savoir si le rayon de direction objet->lumiere intersecte un autre objet 
	t_light 	*curr;
	t_ray 		obj_to_light;

	curr = app->p_data.lights;
	intensity = 0;
	obj_to_light.origin = ray.hit_info.hit_point;
	while (curr)
	{
		obj_to_light.direction = get_directional_vect(ray.hit_info.hit_point, curr->p); // light_direction, aka L
		
		// détermine si l'objet est éclairé par la source lumineuse
		//ray_traversal_algo(&app->root, &obj_to_light); // mettre &obj_to_light je penseeee
		no_tree_intersections(app->p_data.objects, &obj_to_light);

		if (obj_to_light.hit_info.distance != -1)
		{
			r = get_incident_ray_of_light(obj_to_light.direction, ray.hit_info.hit_p_normal);
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

// ray est le rayon incident a l objet dont on veut calculer l'illumination
double 	compute_lighting(t_app *app, float specular, t_ray ray) 
{
	double		intensity;

	intensity = app->p_data.mooooo->infos.ratio;
	intensity += diffuse_reflection(app, ray);
	if (specular != -1)
		intensity += specular_reflection(app, specular, ray);
	return (intensity);
}

