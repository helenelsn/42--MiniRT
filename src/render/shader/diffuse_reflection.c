/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffuse_reflection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 15:54:50 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/16 15:56:06 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/struct.h"
#include "../../../inc/mini_rt.h"

bool 	compute_diffuse(t_light *light, t_ray ray, t_color *color, t_ray obj_to_light)
{
	double 		intensity;
	double		n_dot_l;
		
	n_dot_l = dot(ray.hit_info.outward_normal, obj_to_light.direction);
	if (n_dot_l <= 0.0)
		return (false);
	intensity = light->infos.ratio / M_PI * (n_dot_l); //0.6 * 
	*color = color_add(*color, color_scale(color_mult(light->infos.color, ray.hit_info.color), intensity));
	return (true);
}
