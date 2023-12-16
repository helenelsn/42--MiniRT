/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_inter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/12/16 20:48:25 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/mini_rt.h"

// t_vlist    *get_inter(t_vlist *elem, t_droite d) //clairement pas void mais j'ai pas d'idée
// {
//     if (elem->type == sphere)
//         get_inter_for_sphere((t_sphere *) elem->content, d);
//     else if (elem->type == plan)
//         get_inter_for_plan((t_plan *) elem->content, d);
    
//     return (NULL); // pour que ça compile
// }

void    set_texture_material(t_ray *ray, t_hit_info *closest_obj, void *object)
{
    closest_obj->color = checker_color_at(object, *closest_obj);
    
    closest_obj->outward_normal = get_unit_normal(*closest_obj, closest_obj->hit_point);
     if (dot(ray->direction, closest_obj->outward_normal) > 0.0)
        closest_obj->outward_normal = vect_double_multiply(-1, closest_obj->outward_normal);
	if (closest_obj->obj_mat.textures.t != no_map)
		closest_obj->outward_normal = get_normal_perturbation(*closest_obj, object);
    
    // cas ou est dans l'objet : dans quel sens doit pointer la normale ? 
}

bool    intersect(t_vlist *obj, t_ray *ray)
{
    ray->hit_info.distance = -1;
    if (!obj)
        return false;
    if (obj->type == sphere)
        return (intersect_sphere(ray, obj->content));
    if (obj->type == plan) 
        return (intersect_plan(ray, obj->content));
    if (obj->type == cylindre)
        return (intersect_cylindre(ray, obj->content));
    if (obj->type == cone)
        return (intersect_cone(ray, obj->content));
    // if (obj->type == cone)
    //     return (intersect_cone(ray, obj->content));
    return false;
}

void	no_tree_intersections(t_app *app, t_ray *ray, t_interval t)
{
    t_vlist     *obj;
    t_hit_info  closest_obj;
    double 		min_dist;
	static int print;

    // closest_obj = ft_calloc(sizeof(t_hit_info), 1);
    // if (!closest_obj)
    //     return ;
    // ft_vlstadd_back(app-> ft_vlstnew(elem, free, sphere));
    
    ft_bzero(&closest_obj, sizeof(t_hit_info));
    min_dist = t.max;
    

    // a modif : repetitif, moche
    
	obj = app->p_data.objects;
	while (obj)
    {
        if (intersect(obj, ray) && ray->hit_info.distance >= t.min
			&& ray->hit_info.distance <= min_dist)
        	{
        	    min_dist = ray->hit_info.distance;
				// set_color_in_mat(obj->content, &obj->material, obj->type);
				// set_specular_in_mat(obj->content, &obj->material, obj->type);
        	    copy_obj_properties(obj, &closest_obj, ray->hit_info);
                set_texture_material(ray, &closest_obj, obj->content);
			}
        obj = obj->next;
    }
	
	obj = app->p_data.planes;
	while (obj)
    {
		// set_specular_in_mat(obj->content, &obj->material, obj->type);
		// set_color_in_mat(obj->content, &obj->material, obj->type);
        if (intersect(obj, ray) && ray->hit_info.distance >= t.min
			&& ray->hit_info.distance < min_dist)
        	{
        	    min_dist = ray->hit_info.distance;
        	    copy_obj_properties(obj, &closest_obj, ray->hit_info);
				set_texture_material(ray, &closest_obj, obj->content);
        	}
        obj = obj->next;
    }

    
    
    if (min_dist < t.max)
    {
        // a verifier
        ray->hit_info = closest_obj;
        ray->hit_info.distance = min_dist;
        return ;
    }
    ray->hit_info.distance = -1;
}