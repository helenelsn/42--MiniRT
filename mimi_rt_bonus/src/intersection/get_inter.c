/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_inter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 02:48:39 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/17 22:51:23 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt_bonus.h"

void	set_texture_material(t_ray *ray, t_hit_info *closest_obj, void *object)
{
	closest_obj->color = checker_color_at(object, *closest_obj);
	closest_obj->outward_normal = get_unit_normal(*closest_obj,
			closest_obj->hit_point);
	if (dot(ray->direction, closest_obj->outward_normal) > 0.0)
		closest_obj->outward_normal = vect_double_multiply(-1,
				closest_obj->outward_normal);
	if (closest_obj->obj_mat.textures.t != no_map)
		closest_obj->outward_normal = get_normal_perturbation(*closest_obj,
				object);
}

bool	intersect(t_vlist *obj, t_ray *ray)
{
	ray->hit_info.distance = -1;
	if (!obj)
		return (false);
	if (obj->type == sphere)
		return (intersect_sphere(ray, obj->content));
	if (obj->type == plan)
		return (intersect_plan(ray, obj->content));
	if (obj->type == cylindre)
		return (intersect_cylindre(ray, obj->content));
	if (obj->type == cone)
		return (intersect_cone(ray, obj->content));
	return (false);
}

double	parse_list(t_vlist *list, t_hit_info *closest_obj, t_ray *ray,
		t_interval t)
{
	double	min_dist;
	t_vlist	*obj;

	obj = list;
	min_dist = t.max;
	while (obj)
	{
		if (intersect(obj, ray) && ray->hit_info.distance >= t.min
			&& ray->hit_info.distance <= min_dist)
		{
			min_dist = ray->hit_info.distance;
			copy_obj_properties(obj, closest_obj, ray->hit_info);
			set_texture_material(ray, closest_obj, obj->content);
		}
		obj = obj->next;
	}
	return (min_dist);
}

void	no_tree_intersections(t_app *app, t_ray *ray, t_interval t)
{
	t_hit_info	closest_obj;
	double		min_dist;

	ft_bzero(&closest_obj, sizeof(t_hit_info));
	min_dist = parse_list(app->p_data.objects, &closest_obj, ray, t);
	min_dist = parse_list(app->p_data.planes, &closest_obj, ray,
			get_interval(t.min, min_dist));
	if (min_dist < t.max)
	{
		ray->hit_info = closest_obj;
		ray->hit_info.distance = min_dist;
		return ;
	}
	ray->hit_info.distance = -1;
}
