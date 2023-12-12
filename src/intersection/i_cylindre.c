/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_cylindre.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 00:52:41 by srapin            #+#    #+#             */
/*   Updated: 2023/12/12 19:59:14 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

double	pow2(double n)
{
	return (n * n);
}

t_point get_ray_point(t_ray ray, double t)
{
    t_point p;

    p.x =ray.origin.x + t * ray.direction.x;
    p.y =ray.origin.y + t * ray.direction.y;
    p.z =ray.origin.z + t * ray.direction.z;
    return p;
}

double ft_min_and_positiv(double a, double b)
{
    if (a < 0 && b < 0)
        return 0;
    if (a < 0)
        return b;
    if (b < 0)
        return a;
    return ft_min(a, b);
}

int	solve_quadratic(t_quadratic *f)
{
	double	discr;
	double	res;

	discr = (f->b * f->b) - 4 * f->a * f->c;
	if (discr < 0.0)
		return (0);
	if (discr == 0.0)
	{
		f->t_1 = -0.5 * f->b / f->a;
		f->t_2 = f->t_1;
	}
	else
	{
		if (f->b > 0.0)
			res = -0.5 * (f->b + sqrt(discr));
		else
			res = -0.5 * (f->b - sqrt(discr));
		f->t_1 = res / f->a;
		f->t_2 = f->c / res;
	}
	return (1);
}

int	intersect_cylinder_tube(t_ray *ray, t_cylindre *cylinder, t_quadratic *f)
{
	t_vec	w;
	double	dot_ray_dir_cyl_dir;
	double	dot_w_cylinder_dir;

	w = get_directional_vect( cylinder->p, ray->origin);
	dot_ray_dir_cyl_dir = dot((ray->direction), (cylinder->vec));
	dot_w_cylinder_dir = dot(w, (cylinder->vec));
	f->a = 1 - pow2(dot_ray_dir_cyl_dir);
	f->b = 2 * (dot((ray->direction), w)
			- dot_ray_dir_cyl_dir * dot_w_cylinder_dir);
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

int	intersect_plane(t_ray *ray,t_plan	*plane, double *t)
{
	double	d;
	double	n_ray_dot;
	
    
	n_ray_dot = dot((plane->vec), (ray->direction));
	if (n_ray_dot == 0.0)
	{
		*t = 0;
		return (0);
	}
	d = dot((plane->vec), (t_vec) {plane->p.x ,plane->p.y ,plane->p.z ,1  });
	*t = (d - dot((plane->vec), (t_vec) {ray->origin.x ,ray->origin.y ,ray->origin.z ,1  })) / n_ray_dot;
	return (*t > 0.0);
}

int	intersect_cylinder_covers(t_ray *ray, t_cylindre *cylinder, double *t,
	t_quadratic *f)
{
	double	t_1;
	double	t_2;
    t_point tmp;

	intersect_plane(ray, (void *)&(cylinder->cover_planes[0]), &t_1);
	intersect_plane(ray, (void *)&(cylinder->cover_planes[1]), &t_2);
    // t_1 = get_inter_for_plan(&cylinder->cover_planes[0], (t_droite) {ray->origin, ray->direction}, &tmp);
    // t_2 = get_inter_for_plan(&cylinder->cover_planes[0], (t_droite) {ray->origin, ray->direction}, &tmp);
	*t = ft_min_and_positiv(t_1, t_2);
	return (*t > 0.0 && ((*t > f->t_1 && *t < f->t_2)
			|| (*t < f->t_1 && *t > f->t_2)));
}

bool    get_inter_for_cylindre(t_cylindre *cy, t_ray r, double *d)
{
    t_quadratic q;
    double t_cover;
    double t;

    
    t_vec	w;
	double	dot_ray_dir_cyl_dir;
	double	dot_w_cylinder_dir;
    t_point tmp;
    // printf("\n from hier");
    // normalise(&r.direction);
    
	if (!intersect_cylinder_tube(&r, cy, &q))
		return (false);
    t = ft_min_and_positiv(q.t_1,q.t_2 );
    if (t <=0)
        return false;
    cut_cylinder(&r, cy, &t);
    if (intersect_cylinder_covers(&r, cy, &t_cover, &q))
		t = ft_min_and_positiv(t_cover, t);
    *d = t;
    // return t > 0;
    return true;

}

bool    intersect_cylindre(t_ray *ray, void *object)
{
    t_cylindre      *cy;
    t_droite    d;
    t_point  res;
    double t;
    
    
    cy = object;
    d.p = ray->origin;
    d.v = ray->direction;

    if (!get_inter_for_cylindre(cy, *ray, &t))
        return false;
    ray->hit_info.coef  = t;
    if (ray->hit_info.coef <= 0)
        return false;

    res.x = ray->origin.x + ray->hit_info.coef * ray->direction.x;
    res.y = ray->origin.y + ray->hit_info.coef * ray->direction.y;
    res.z = ray->origin.z + ray->hit_info.coef * ray->direction.z;
    ray->hit_info.hit_point = res;
    ray->hit_info.distance = get_dist_between_points(ray->origin, ray->hit_info.hit_point);

    // printf("---------------------- intersected plan\n");

    return (true);
}