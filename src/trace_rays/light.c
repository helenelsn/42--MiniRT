/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 18:15:45 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/14 16:04:08 by hlesny           ###   ########.fr       */
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
// double 	specular_reflection(t_app *app, t_ray ray)
// {
// 	double 		intensity;
// 	t_vec		r;
// 	double 		obj_to_light_dist;
// 	t_light 	*curr;
// 	t_ray 		obj_to_light;

// 	curr = app->p_data.lights;
// 	intensity = 0;
// 	obj_to_light.origin = ray.hit_info.hit_point;
// 	while (curr)
// 	{		
// 		obj_to_light.direction = get_directional_vect(ray.hit_info.hit_point, curr->p); // light_direction, aka L
// 		obj_to_light_dist = obj_to_light.direction.norm;
// 		normalise(&obj_to_light.direction);
		
		
// 		//ray_traversal_algo(&app->root, &obj_to_light); // mettre &obj_to_light je penseeee
// 		no_tree_intersections(app->p_data, &obj_to_light, get_interval(HITPOINT_OFFSET, obj_to_light_dist));

// 		// détermine si l'objet est éclairé par la source lumineuse
// 		if (obj_to_light.hit_info.distance == -1)
// 		{
// 			// Catch degenerate scatter direction
//         	// if (scatter_direction.near_zero())
//             // scatter_direction = rec.normal;

			
			
// 			r = get_incident_ray_of_light(obj_to_light.direction, ray.hit_info.outward_normal);
// 			// r = reflect_ray(ray.direction, ray.hit_info.outward_normal);
			
// 			r.norm = get_v_norm(r);
// 			normalise(&r);
			
// 			double r_dot_v = dot(r, vect_double_multiply(-1, ray.direction)); //ray.hit_info.reflected_ray);
// 			double n_dot_l = dot(ray.hit_info.outward_normal, obj_to_light.direction);
// 			if (r_dot_v > 0.0)
// 			{
// 				// 0.4 == reflectance_coefficient
// 				intensity += 0.4 * curr->infos.ratio * pow(r_dot_v, ray.hit_info.obj_mat.specular) * n_dot_l;	// / (r.norm * obj_to_light.direction.norm )
				
// 				// printf("{%s} : color = %u\n", __func__, color.hex);
// 			}
// 		}
// 		curr = curr->next;
// 	}
// 	return (intensity);
// }


// /* matte objects */
// double	diffuse_reflection(t_app *app, t_ray ray)
// {
// 	double 		intensity;
// 	double		n_dot_l;
// 	double 		obj_to_light_dist;
// 	t_ray		obj_to_light; 
// 	t_light 	*curr;

// 	intensity = 0;
// 	curr = app->p_data.lights;
// 	obj_to_light.origin = ray.hit_info.hit_point;
// 	while (curr)
// 	{
// 		obj_to_light.direction = get_directional_vect(ray.hit_info.hit_point, curr->p);  // light_direction, aka L
// 		obj_to_light_dist = obj_to_light.direction.norm;
// 		normalise(&obj_to_light.direction);
		
// 		// détermine si l'objet est éclairé par la source lumineuse
// 		//ray_traversal_algo(&app->root, &obj_to_light);
// 		no_tree_intersections(app->p_data, &obj_to_light, get_interval(HITPOINT_OFFSET, obj_to_light_dist));
		
// 		if (obj_to_light.hit_info.distance == -1) // set a -1 si le rayon n'intersecte pas d'objets
// 		{
// 			n_dot_l = dot(ray.hit_info.outward_normal, obj_to_light.direction);
// 			if (n_dot_l > 0.0)
// 			{
// 				intensity += 0.6 * curr->infos.ratio / M_PI * (n_dot_l); // / dot(obj_to_light.direction.norm, obj_to_light.direction.norm); // /(ray.hit_info.outward_normal.norm * obj_to_light.direction.norm); // peut simplifier, normalemet les deux sont unitaires et ont donc une norme de 1
// 				// printf("{%s} : color = %u\n", __func__, color.hex);
// 			}
// 		}
// 		curr = curr->next;
// 	}
// 	return (intensity);
// }

// t_color 	compute_lighting(t_app *app, t_ray ray) 
// {
// 	double		intensity;
	
// 	intensity = app->p_data.mooooo->infos.ratio;
// 	intensity += diffuse_reflection(app, ray);
	
	
// 	if (ray.hit_info.obj_mat.specular > 0)
// 	{
// 		intensity += specular_reflection(app, ray);
// 	}
	
// 	return (intensity);
// }

void 	compute_specular(t_light *light, t_ray ray, t_color *color, t_ray obj_to_light)
{
	double 		intensity;
	t_vec		r;

	if (ray.hit_info.obj_mat.specular == -1)
		return ;	

	r = get_incident_ray_of_light(obj_to_light.direction, ray.hit_info.outward_normal);
	// r = reflect_ray(ray.direction, ray.hit_info.outward_normal);
	r.norm = get_v_norm(r);
	normalise(&r);	
	double r_dot_v = dot(r, vect_double_multiply(-1, ray.direction)); //ray.hit_info.reflected_ray);
	double n_dot_l = dot(ray.hit_info.outward_normal, obj_to_light.direction);
	if (r_dot_v <= 0.0)
		return ;
	
	intensity = light->infos.ratio * pow(r_dot_v, ray.hit_info.obj_mat.specular) * n_dot_l;	//0.4 *  // / (r.norm * obj_to_light.direction.norm )
	// *color = color_add(*color, color_scale(light->infos.color, intensity));
	*color = color_add(*color, color_scale(color_mult(light->infos.color, ray.hit_info.obj_mat.color), intensity));
}


bool 	compute_diffuse(t_light *light, t_ray ray, t_color *color, t_ray obj_to_light)
{
	double 		intensity;
	double		n_dot_l;
		
	n_dot_l = dot(ray.hit_info.outward_normal, obj_to_light.direction);
	if (n_dot_l <= 0.0)
		return (false);
	intensity = light->infos.ratio / M_PI * (n_dot_l); //0.6 *  // / dot(obj_to_light.direction.norm, obj_to_light.direction.norm); // /(ray.hit_info.outward_normal.norm * obj_to_light.direction.norm); // peut simplifier, normalemet les deux sont unitaires et ont donc une norme de 1
	// *color = color_add(*color, color_scale(light->infos.color, intensity));
	*color = color_add(*color, color_scale(color_mult(light->infos.color, ray.hit_info.obj_mat.color), intensity));
	return (true);
}

void 	compute_ambiant(t_light *light, t_ray ray, t_color *color, t_color amb_color)
{
	t_color		emitted_color;

	emitted_color = color_mult(ray.hit_info.obj_mat.color, light->infos.color);
	*color = color_mult(emitted_color, amb_color);
}

bool	is_directly_illuminated(t_app *app, t_light *light, t_ray ray, t_ray *obj_to_light)
{
	double 		obj_to_light_dist;

	obj_to_light->origin = ray.hit_info.hit_point;
	obj_to_light->direction = get_directional_vect(ray.hit_info.hit_point, light->p);  // light_direction, aka L
	obj_to_light_dist = obj_to_light->direction.norm;
	normalise(&obj_to_light->direction);

	//ray_traversal_algo(&app->root, &obj_to_light);
	no_tree_intersections(app->p_data, obj_to_light, get_interval(HITPOINT_OFFSET, obj_to_light_dist));
	return (obj_to_light->hit_info.distance == -1);
}


// a mettre ailleurs !! (a besoin de le faire qu'une fois pour chaque lumiere)
void	set_emitted_colors(t_light *light, t_mood_light *amb)
{
	t_light *curr_light;

	curr_light = light;
	amb->infos.emitted_color = color_scale(amb->infos.color, amb->infos.ratio);
	while (curr_light)
	{
		curr_light->infos.emitted_color = color_scale(curr_light->infos.color, curr_light->infos.ratio);
		curr_light = curr_light->next;
	}
}

t_color		compute_lighting(t_app *app, t_ray ray)
{
	t_color 	color;
	t_light		*light;
	double 		obj_to_light_dist;
	t_ray		obj_to_light;

	ft_bzero(&color, sizeof(t_color));
	light = app->p_data.lights;

	// a mettre ailleurs (genre avant trace_ray)
	set_emitted_colors(app->p_data.lights, app->p_data.mooooo);
	
	t_color effective_color = color_mult(app->p_data.mooooo->infos.emitted_color, ray.hit_info.obj_mat.color);
	while (light)
	{
		ft_bzero(&obj_to_light, sizeof(t_ray));
		color.hex = 0;
		
		if (is_directly_illuminated(app, light, ray, &obj_to_light)
			&& compute_diffuse(light, ray, &color, obj_to_light))
				compute_specular(light, ray, &color, obj_to_light);
		effective_color = color_add(effective_color, color);
		light = light->next;
	}
	return (effective_color);
}
