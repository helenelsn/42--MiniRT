/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_cone.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 19:29:00 by srapin            #+#    #+#             */
/*   Updated: 2023/12/14 00:16:09 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

int	cut_cone_surface(t_cone *cone, t_point hit_point, double *t)
{
	t_vec	hit_to_center;
	double	projected_height;

	if (*t <= 0.0)
		return (0);
	hit_to_center = get_directional_vect(cone->p, hit_point);
	projected_height = dot(hit_to_center, (cone->vec));
	if (projected_height <= cone->height && projected_height >= 0.0)
		return (1);
	*t = 0.0;
	return (0);
}


int	intersect_entire_cone(t_ray *ray, t_cone *cone, t_quadratic *f)
{
	t_vec	w;
	double	m;
	double	dot_ray_dir_h;
	double	dot_w_h;
	double	dot_w_h_squared;

	m = pow2(cone->radius) / pow2(cone->height);
	w = get_directional_vect(cone->top, ray->origin);
	dot_ray_dir_h = dot((ray->direction), (cone->vec));
	dot_w_h = dot(w, (cone->vec));
	dot_w_h_squared = pow2(dot_w_h);
	f->a = 1 - m * pow2(dot_ray_dir_h) - pow2(dot_ray_dir_h);
	f->b = 2 * (dot((ray->direction), w) - m
			* dot_ray_dir_h * dot_w_h - dot_ray_dir_h * dot_w_h);
	f->c = dot(w, w) - m * dot_w_h_squared - dot_w_h_squared;
	return (solve_quadratic(f));
}


bool    get_inter_for_cone(t_cone *co, t_ray r, double *d)
{
    t_quadratic	f;
	double		t_base = -1;

	if (!intersect_entire_cone(&r, co, &f))
		return (false);
	if (dot((co->vec), (r.direction)) > 0)
	{
		*d = ft_min_and_positiv(f.t_1, f.t_2);
		cut_cone_surface(co, get_ray_point(r, *d), d);
	}
	else
	{
		cut_cone_surface(co, get_ray_point(r, f.t_1), &f.t_1);
		cut_cone_surface(co, get_ray_point(r, f.t_2), &f.t_2);
		*d = ft_min_and_positiv(f.t_1, f.t_2);
	}
	intersect_circle(&r, (t_circle) {co->cover_plane, co->p, co->radius}, &t_base);
	*d = ft_min_and_positiv(*d, t_base);
	return (*d > 0.0);
}

bool    intersect_cone(t_ray *ray, void *object)
{
    t_cone      *co;
    t_point  res;
    double t = 0.0;
    
    
    co = object;
	int flag = get_inter_for_cone(co, *ray, &t);
	// if (t && t != 1)
	// 	printf("res =%f\n ", t);
	
    if (!flag)
        return false;
		// printf("res =%d ", flag);
    ray->hit_info.coef  = t;
    if (ray->hit_info.coef <= 0.0)
        return false;

    res = get_ray_point(*ray, ray->hit_info.coef);
    ray->hit_info.hit_point = res;
    ray->hit_info.distance = get_dist_between_points(ray->origin, ray->hit_info.hit_point);
	// if (t!= 1)
	// printf("end of %s %f\n", __func__, ray->hit_info.distance);	

    // printf("---------------------- intersected plan\n");

    return (true);
}