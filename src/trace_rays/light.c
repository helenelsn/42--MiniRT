/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eva <eva@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 18:15:45 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/10 01:16:53 by eva              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/struct.h"
#include "../../inc/mini_rt.h"

/* ------------- LIGHT -------------- */

/*  pour un point d'intersection P, n la normale a la surface de l'objet en ce point.
et v le vecteur directeur de l'origine du rayon a P // de P a l'origine du rayon */
t_vec	reflect_ray(t_vec v, t_vec n)
{
	return (vect_substract(v, vect_double_multiply(2 * dot(v, n), n)));
}

/*  pour un point d'intersection P, n la normale a la surface de l'objet en ce point.
et l le vecteur directeur de l'origine du rayon a P */
t_vec get_incident_ray_of_light(t_vec l, t_vec n)
{
	// R⃗ =2N⃗ ⟨N⃗ ,L⃗ ⟩−L⃗
	// vect_double_multiply(2 * dot(n, l), n), 
	// return (vect_substract(l, vect_double_multiply(2 * dot(n, l), n)));
	return (vect_substract(vect_double_multiply(2 * dot(n, l), n), l));
	// return (vect_substract(vect_double_multiply(2, vect_double_multiply(dot(n, l), n)), l));
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
double 	specular_reflection(t_app *app, t_ray ray)
{
	double 		intensity;
	t_vec		r;
	double 		obj_to_light_dist;
	t_light 	*curr;
	t_ray 		obj_to_light;

	t_color color;
	ft_bzero(&color, sizeof(t_color));

	curr = app->p_data.lights;
	intensity = 0;
	obj_to_light.origin = ray.hit_info.hit_point;
	while (curr)
	{
		// intensity = 0;
		
		obj_to_light.direction = get_directional_vect(ray.hit_info.hit_point, curr->p); // light_direction, aka L
		obj_to_light_dist = obj_to_light.direction.norm;
		normalise(&obj_to_light.direction);
		
		
		//ray_traversal_algo(&app->root, &obj_to_light); // mettre &obj_to_light je penseeee
		no_tree_intersections(app->p_data, &obj_to_light, get_interval(HITPOINT_OFFSET, obj_to_light_dist));

		// détermine si l'objet est éclairé par la source lumineuse
		if (obj_to_light.hit_info.distance == -1)
		{
			// Catch degenerate scatter direction
        	// if (scatter_direction.near_zero())
            // scatter_direction = rec.normal;

			
			
			r = get_incident_ray_of_light(obj_to_light.direction, ray.hit_info.outward_normal);
			// r = reflect_ray(ray.direction, ray.hit_info.outward_normal);
			
			r.norm = get_v_norm(r);
			normalise(&r);
			
			double r_dot_v = dot(r, vect_double_multiply(-1, ray.direction)); //ray.hit_info.reflected_ray);
			double n_dot_l = dot(ray.hit_info.outward_normal, obj_to_light.direction);
			if (r_dot_v > 0.0)
			{
				// 0.4 == reflectance_coefficient
				intensity += 0.4 * curr->infos.ratio * pow(r_dot_v, ray.hit_info.obj_mat.specular) * n_dot_l;	// / (r.norm * obj_to_light.direction.norm )
				
				// t_vec reflected_ray = reflect_ray(ray.direction, ray.hit_info.outward_normal); // ou juste ray.direction en premier argument ?
				// t_color reflected_color = trace_ray(app, ray.hit_info.hit_point, reflected_ray, rebound_nb + 1);
				
				// intensity = 0.4 * curr->infos.ratio * pow(r_dot_v, ray.hit_info.obj_mat.specular) * n_dot_l;
				// color = color_add(color, color_scale(curr->infos.color, intensity));
				// printf("{%s} : color = %u\n", __func__, color.hex);
			}
		}
		curr = curr->next;
	}
	// return (color);
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

	t_color color;
	ft_bzero(&color, sizeof(t_color));
	
	intensity = 0;
	curr = app->p_data.lights;
	obj_to_light.origin = ray.hit_info.hit_point;
	while (curr)
	{
		// intensity = 0;
		obj_to_light.direction = get_directional_vect(ray.hit_info.hit_point, curr->p);  // light_direction, aka L
		obj_to_light_dist = obj_to_light.direction.norm;
		normalise(&obj_to_light.direction);
		
		// détermine si l'objet est éclairé par la source lumineuse
		//ray_traversal_algo(&app->root, &obj_to_light);
		no_tree_intersections(app->p_data, &obj_to_light, get_interval(HITPOINT_OFFSET, obj_to_light_dist));
		
		if (obj_to_light.hit_info.distance == -1) // set a -1 si le rayon n'intersecte pas d'objets
		{
			n_dot_l = dot(ray.hit_info.outward_normal, obj_to_light.direction);
			if (n_dot_l > 0.0)
			{
				intensity += 0.6 * curr->infos.ratio / M_PI * (n_dot_l); // / dot(obj_to_light.direction.norm, obj_to_light.direction.norm); // /(ray.hit_info.outward_normal.norm * obj_to_light.direction.norm); // peut simplifier, normalemet les deux sont unitaires et ont donc une norme de 1
				// intensity = 0.6 * curr->infos.ratio / M_PI * (n_dot_l);
				// color = color_add(color, color_scale(curr->infos.color, intensity));
				// printf("{%s} : color = %u\n", __func__, color.hex);
			}
		}
		curr = curr->next;
	}
	// return (color);
	return (intensity);
}

double 	compute_lighting(t_app *app, t_ray ray) 
{
	double		intensity;
	t_color		lights_color;

	ft_bzero(&lights_color, sizeof(t_color));
	
	intensity = app->p_data.mooooo->infos.ratio;
	intensity += diffuse_reflection(app, ray);
	
	// lights_color = color_scale(app->p_data.mooooo->infos.color, app->p_data.mooooo->infos.ratio);
	// lights_color = color_add(lights_color, diffuse_reflection(app, ray));
	
	
	if (ray.hit_info.obj_mat.specular > 0)
	{
		intensity += specular_reflection(app, ray);
		// lights_color = color_add(lights_color, specular_reflection(app, ray));
	}
	
	// return (lights_color);
	return (intensity);
}
