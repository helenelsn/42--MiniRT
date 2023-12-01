/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 18:15:45 by hlesny            #+#    #+#             */
/*   Updated: 2023/11/30 23:01:02 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/struct.h"
#include "../../inc/mini_rt.h"

/* ------------- LIGHT -------------- */

t_vec_3d	reflect_ray(t_vec_3d v, t_vec_3d n)
{
	return (vect_substract(v, vect_double_multiply(2 * vec_x_vec_scal(v, n), n)));
}

t_vec_3d get_incident_ray_of_light(t_vec_3d l, t_vec_3d n)
{
	// R⃗ =2N⃗ ⟨N⃗ ,L⃗ ⟩−L⃗
	
	return (vect_substract(vect_double_multiply(2 * vec_x_vec_scal(n, l), n), l));
	// return (vect_substract(vect_double_multiply(2, vect_double_multiply(vec_x_vec_scal(n, l), n)), l));
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
	double 		obj_to_light_dist;
	//t_hit_info	closest_hit; // savoir si le rayon de direction objet->lumiere intersecte un autre objet 
	t_light 	*curr;
	t_ray 		obj_to_light;

	curr = app->p_data.lights;
	intensity = 0;
	obj_to_light.origin = ray.hit_info.hit_point;
	while (curr)
	{
		obj_to_light.direction = get_directional_vect(ray.hit_info.hit_point, curr->p); // light_direction, aka L
		obj_to_light_dist = obj_to_light.direction.norm;
		normalise(&obj_to_light.direction);
		
		
		//ray_traversal_algo(&app->root, &obj_to_light); // mettre &obj_to_light je penseeee
		no_tree_intersections(app->p_data, &obj_to_light, get_interval(HITPOINT_OFFSET, obj_to_light_dist));

		// détermine si l'objet est éclairé par la source lumineuse
		if (obj_to_light.hit_info.distance == -1)
		{
			r = get_incident_ray_of_light(obj_to_light.direction, ray.hit_info.outward_normal);
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


/* matte objects */
double	diffuse_reflection(t_app *app, t_ray ray)
{
	double 		intensity;
	double		n_dot_l;
	double 		obj_to_light_dist;
	t_ray		obj_to_light; 
	t_light 	*curr;

	curr = app->p_data.lights;
	intensity = 0;
	obj_to_light.origin = ray.hit_info.hit_point;
	while (curr)
	{
		obj_to_light.direction = get_directional_vect(ray.hit_info.hit_point, curr->p);  // light_direction, aka L
		obj_to_light_dist = obj_to_light.direction.norm;
		normalise(&obj_to_light.direction);
		
		// détermine si l'objet est éclairé par la source lumineuse
		//ray_traversal_algo(&app->root, &obj_to_light);
		no_tree_intersections(app->p_data, &obj_to_light, get_interval(HITPOINT_OFFSET, obj_to_light_dist));
		
		if (obj_to_light.hit_info.distance == -1) // set a -1 si le rayon n'intersecte pas d'objets
		{
			n_dot_l = vec_x_vec_scal(ray.hit_info.outward_normal, obj_to_light.direction);
			if (n_dot_l > 0.0)
				intensity += curr->infos.ratio * n_dot_l/(ray.hit_info.outward_normal.norm * obj_to_light.direction.norm);
		}
		curr = curr->next;
	}
	return (intensity);
}

double 	compute_lighting(t_app *app, float specular, t_ray ray) 
{
	double		intensity;

	intensity = app->p_data.mooooo->infos.ratio;
	intensity += diffuse_reflection(app, ray);
	// if (specular != -1)
	// 	intensity += specular_reflection(app, specular, ray);
	// printf("{%s}, intensity = %");
	return (intensity);
}

