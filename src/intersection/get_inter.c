/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_inter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Helene <Helene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/12/15 19:25:06 by Helene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

void    set_texture_material(t_ray *ray, t_hit_info *closest_obj, void *object)
{
    closest_obj->color = checker_color_at(object, *closest_obj);
    
    closest_obj->outward_normal = get_unit_normal(*closest_obj, closest_obj->hit_point);
    if (dot(ray->direction, closest_obj->outward_normal) > 0.0)
        closest_obj->outward_normal = vect_double_multiply(-1, closest_obj->outward_normal);
	if (closest_obj->obj_mat.textures.bump_mapping)
		closest_obj->outward_normal = get_normal_perturbation(*closest_obj, object);
    // if (closest_obj->texture_normal.)  
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

double    parse_objects(t_vlist *obj, t_ray *ray, t_hit_info *closest_obj, t_interval t)
{
    double  min_dist;

    min_dist = t.max;
    while (obj)
    {
        if (intersect(obj, ray) && ray->hit_info.distance >= t.min
			&& ray->hit_info.distance <= min_dist)
        	{
        	    min_dist = ray->hit_info.distance;
        	    copy_obj_properties(obj, closest_obj, ray->hit_info); // peut tej du coup nn ?
                set_texture_material(ray, closest_obj, obj->content);
			}
        obj = obj->next;
    }
    
    return (min_dist);
}    

void	no_tree_intersections(t_parsing_data pdata, t_ray *ray, t_interval t)
{
    t_vlist     *obj;
    t_hit_info  *closest_obj;
    double 		min_dist;

    closest_obj = ft_calloc(sizeof(t_hit_info), 1);
    if (!closest_obj)
        return ;
    min_dist = t.max;

    ray->hit_info.distance = -1;

    
	obj = pdata.objects;
	while (obj)
    {
        if (intersect(obj, ray) && ray->hit_info.distance >= t.min
			&& ray->hit_info.distance <= min_dist)
        	{
        	    min_dist = ray->hit_info.distance;
				// set_color_in_mat(obj->content, &obj->material, obj->type);
				// set_specular_in_mat(obj->content, &obj->material, obj->type);
        	    copy_obj_properties(obj, closest_obj, ray->hit_info);
                set_texture_material(ray, closest_obj, obj->content);
			}
        obj = obj->next;
    }
	
	obj = pdata.planes;
	while (obj)
    {
		// set_specular_in_mat(obj->content, &obj->material, obj->type);
		// set_color_in_mat(obj->content, &obj->material, obj->type);
        if (intersect(obj, ray) && ray->hit_info.distance >= t.min
			&& ray->hit_info.distance < min_dist)
        	{
        	    min_dist = ray->hit_info.distance;
        	    copy_obj_properties(obj, closest_obj, ray->hit_info);
				set_texture_material(ray, closest_obj, obj->content);
        	}
        obj = obj->next;
    }

    /* ------------ normed version -------------------- */
    
    min_dist = parse_objects(pdata.objects, ray, closest_obj, t);
    min_dist = parse_objects(pdata.planes, ray, closest_obj, get_interval(t.min, min_dist));
    
    /* -------------------------------- */

    
    if (min_dist < t.max)
    {
        ray->hit_info = *closest_obj;
        ray->hit_info.distance = min_dist;
        return ;
    }
    //ray->hit_info.distance = -1;
}