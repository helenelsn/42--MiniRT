/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_plan.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 00:10:31 by srapin            #+#    #+#             */
/*   Updated: 2023/12/17 22:51:23 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt_bonus.h"

int	get_inter_for_plan(t_plan *p, t_droite d, t_point *res)
{
	double	t;

	normalise(&d.v);
	if (!(p->a * d.v.x + p->b * d.v.y + p->c * d.v.z))
		return (-1);
	t = (p->a * d.p.x + p->b * d.p.y + p->c * d.p.z + p->d) / -(p->a * d.v.x
			+ p->b * d.v.y + p->c * d.v.z);
	res->x = d.p.x + t * d.v.x;
	res->y = d.p.y + t * d.v.y;
	res->z = d.p.z + t * d.v.z;
	return (t);
}

bool	intersect_plan(t_ray *ray, void *object)
{
	t_plan		*p;
	t_droite	d;
	t_point		res;

	p = object;
	d.p = ray->origin;
	d.v = ray->direction;
	ray->hit_info.coef = get_inter_for_plan(p, d, &res);
	if (ray->hit_info.coef < 0.0)
		return (false);
	ray->hit_info.hit_point = res;
	ray->hit_info.distance = get_dist_between_points(ray->origin,
			ray->hit_info.hit_point);
	return (true);
}
