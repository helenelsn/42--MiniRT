/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_model.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 15:55:33 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/16 15:56:38 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/struct.h"
#include "../../../inc/mini_rt.h"

bool	is_directly_illuminated(t_app *app, t_light *light, t_ray ray, t_ray *obj_to_light)
{
	double 		obj_to_light_dist;

	obj_to_light->origin = ray.hit_info.hit_point;
	obj_to_light->direction = get_directional_vect(ray.hit_info.hit_point, light->p);
	obj_to_light_dist = obj_to_light->direction.norm;
	normalise(&obj_to_light->direction);
	no_tree_intersections(app, obj_to_light, get_interval(HITPOINT_OFFSET, obj_to_light_dist));
	return (obj_to_light->hit_info.distance == -1);
}

t_color		compute_lighting(t_app *app, t_ray ray)
{
	t_color 	color;
	t_light		*light;
	double 		obj_to_light_dist;
	t_ray		obj_to_light;

	ft_bzero(&color, sizeof(t_color));
	light = app->p_data.lights;
	t_color effective_color = color_mult(app->p_data.mooooo->infos.emitted_color, ray.hit_info.color);
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
