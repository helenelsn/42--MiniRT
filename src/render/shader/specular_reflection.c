/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular_reflection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 15:54:36 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/17 04:09:58 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/mini_rt.h"
#include "../../../inc/struct.h"

void	compute_specular(t_light *light, t_ray ray, t_color *color,
		t_ray obj_to_light)
{
	double	intensity;
	t_vec	r;
	double	r_dot_v;
	double	n_dot_l;

	if (ray.hit_info.obj_mat.specular == -1)
		return ;
	r = get_incident_ray_of_light(obj_to_light.direction,
			ray.hit_info.outward_normal);
	r.norm = get_v_norm(r);
	normalise(&r);
	r_dot_v = dot(r, vect_double_multiply(-1, ray.direction));
	n_dot_l = dot(ray.hit_info.outward_normal, obj_to_light.direction);
	if (r_dot_v <= 0.0)
		return ;
	intensity = light->infos.ratio * pow(r_dot_v, ray.hit_info.obj_mat.specular)
		* n_dot_l;
	*color = color_add(*color, color_scale(color_mult(light->infos.color,
					ray.hit_info.color), intensity));
}
