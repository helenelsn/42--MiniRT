/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_cylindre_caps.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 03:45:49 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/17 03:51:57 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

int	intersect_plane(t_ray *ray, t_plan *plane, double *t)
{
	double	d;
	double	n_ray_dot;

	n_ray_dot = dot((plane->vec), (ray->direction));
	if (n_ray_dot == 0.0)
	{
		*t = 0;
		return (0);
	}
	d = dot((plane->vec), (t_vec){plane->p.x, plane->p.y, plane->p.z, 1});
	*t = (d - dot((plane->vec), (t_vec){ray->origin.x, ray->origin.y,
				ray->origin.z, 1})) / n_ray_dot;
	return (*t > 0.0);
}

int	intersect_cylinder_covers(t_ray *ray, t_cylindre *cylinder, double *t,
		t_quadratic *f)
{
	double	t_1;
	double	t_2;

	intersect_plane(ray, (void *)&(cylinder->cover_planes[0]), &t_1);
	intersect_plane(ray, (void *)&(cylinder->cover_planes[1]), &t_2);
	*t = ft_min_and_positiv(t_1, t_2);
	return (*t >= 0.0 && ((*t > f->t_1 && *t < f->t_2) || (*t < f->t_1
				&& *t > f->t_2)));
}
