/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_inter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Helene <Helene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:20:33 by srapin            #+#    #+#             */
/*   Updated: 2023/12/12 15:51:59 by Helene           ###   ########.fr       */
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
    // if (obj->type == cone)
    //     return (intersect_cone(ray, obj->content));
    return false;
}

void	no_tree_intersections(t_parsing_data pdata, t_ray *ray, t_interval t)
{
    t_vlist     *obj;
    t_hit_info  *closest_obj;
    double 		min_dist;
	static int print;

    closest_obj = ft_calloc(sizeof(t_hit_info), 1);
    if (!closest_obj)
        return ;
    min_dist = t.max;
    
	obj = pdata.objects;
	while (obj)
    {
        if (intersect(obj, ray) && ray->hit_info.distance >= t.min
			&& ray->hit_info.distance <= min_dist)
        	{
        	    min_dist = ray->hit_info.distance;
				set_color_in_mat(obj->content, &obj->material, obj->type);
				set_specular_in_mat(obj->content, &obj->material, obj->type);
        	    copy_obj_properties(obj, closest_obj, ray->hit_info.hit_point);
			}
        obj = obj->next;
    }
	
	obj = pdata.planes;
	
	
	while (obj)
    {
		set_specular_in_mat(obj->content, &obj->material, obj->type);
		set_color_in_mat(obj->content, &obj->material, obj->type);
        if (intersect(obj, ray) && ray->hit_info.distance >= t.min
			&& ray->hit_info.distance < min_dist)
        	{
        	    min_dist = ray->hit_info.distance;
        	    copy_obj_properties(obj, closest_obj, ray->hit_info.hit_point);
				
        	}
        obj = obj->next;
    }
    

	// a modif : repetitif, moche
	
	
    if (min_dist < t.max)
    {
        // a verifier
        ray->hit_info = *closest_obj;
        ray->hit_info.distance = min_dist;
        return ;
    }
    // ray->hit_info.distance = -1;
}