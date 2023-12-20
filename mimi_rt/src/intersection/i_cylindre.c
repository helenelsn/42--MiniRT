/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_cylindre.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 00:52:41 by srapin            #+#    #+#             */
/*   Updated: 2023/12/21 00:40:11 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

int	intersect_cylinder_tube(t_ray *ray, t_cylindre *cylinder, t_quadratic *f)
{
	t_vec	w;
	double	dot_ray_dir_cyl_dir;
	double	dot_w_cylinder_dir;

	w = get_directional_vect(cylinder->p, ray->origin);
	dot_ray_dir_cyl_dir = dot((ray->direction), (cylinder->vec));
	dot_w_cylinder_dir = dot(w, (cylinder->vec));
	f->a = 1 - pow2(dot_ray_dir_cyl_dir);
	f->b = 2 * (dot((ray->direction), w) - dot_ray_dir_cyl_dir
			* dot_w_cylinder_dir);
	f->c = dot(w, w) - pow2(dot_w_cylinder_dir) - pow2(cylinder->radius);
	return (solve_quadratic(f));
}

int	cut_cylinder(t_ray *ray, t_cylindre *cylinder, double *t)
{
	t_vec	hit_to_center;

	hit_to_center = get_directional_vect(cylinder->p, get_ray_point(*ray, *t));
	if (fabs(dot(hit_to_center, (cylinder->vec))) <= cylinder->height / 2)
		return (1);
	*t = 0.0;
	return (0);
}

bool	get_inter_for_cylindre(t_cylindre *cy, t_ray *r, double *d)
{
	t_quadratic	q;
	double		t_cover;
	double		t;

	if (!intersect_cylinder_tube(r, cy, &q))
		return (false);
	t = ft_min_and_positiv(q.t_1, q.t_2);
	if (t <= 0)
		return (false);
	cut_cylinder(r, cy, &t);
	if (intersect_cylinder_covers(r, cy, &t_cover, &q))
	{
		t = ft_min_and_positiv(t_cover, t);
		if (t == t_cover)
			r->hit_info.cap_hit = true;
	}
	*d = t;
	return (true);
}

bool	intersect_cylindre(t_ray *ray, void *object)
{
	t_cylindre	*cy;
	t_point		res;
	double		t;

	cy = object;
	if (!get_inter_for_cylindre(cy, ray, &t))
		return (false);
	ray->hit_info.coef = t;
	if (ray->hit_info.coef <= 0)
		return (false);
	res.x = ray->origin.x + ray->hit_info.coef * ray->direction.x;
	res.y = ray->origin.y + ray->hit_info.coef * ray->direction.y;
	res.z = ray->origin.z + ray->hit_info.coef * ray->direction.z;
	ray->hit_info.hit_point = res;
	ray->hit_info.distance = get_dist_between_points(ray->origin,
			ray->hit_info.hit_point);
	return (true);
}
