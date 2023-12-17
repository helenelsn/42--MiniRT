/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_sphere.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:19:12 by srapin            #+#    #+#             */
/*   Updated: 2023/12/17 02:07:02 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

bool	intersect_sphere(t_ray *ray, void *object)
{
	t_sphere	*sp;
	t_quadratic	eq;
	t_vec		center_to_origin;
	double		mult;

	sp = object;
	center_to_origin = get_directional_vect(sp->p, ray->origin);
	eq.a = dot(ray->direction, ray->direction);
	eq.b = 2 * dot(center_to_origin, ray->direction);
	eq.c = dot(center_to_origin, center_to_origin) - sp->radius * sp->radius;
	if (!solve_quadratic_eq(&eq))
		return (false);
	mult = get_closest_point(eq.t_1, eq.t_2);
	ray->hit_info.hit_point.x = ray->origin.x + ray->direction.x * mult;
	ray->hit_info.hit_point.y = ray->origin.y + ray->direction.y * mult;
	ray->hit_info.hit_point.z = ray->origin.z + ray->direction.z * mult;
	ray->hit_info.coef = mult;
	ray->hit_info.distance = get_dist_between_points(ray->origin,
			ray->hit_info.hit_point);
	if (ray->hit_info.coef <= 0.001)
		ray->hit_info.distance = -1;
	return (ray->hit_info.distance != -1);
}
