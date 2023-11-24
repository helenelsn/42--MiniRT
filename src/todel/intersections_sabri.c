
#include "../../inc/struct.h"
#include "../../inc/mini_rt.h"
#include "../../inc/bsp.h"

typedef struct t_quadratic
{
	double	a;
	double	b;
	double	c;
	double	t_1;
	double	t_2;
}				t_quadratic;


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



/*  --------------- sphere ------------------- */

int	intersect_sphere(t_ray *ray, void *shape, double *t, int *is_surface_hit)
{
	t_quadratic	f;
	t_sphere	*sphere;
	t_vec		w;

	(void)is_surface_hit;
	sphere = (t_sphere *)shape;
	w = sub(ray->origin, sphere->center);
	f.a = 1.0;
	f.b = 2 * dot(&(ray->dir), &w);
	f.c = dot(&w, &w) - pow2(sphere->radius);
	if (!solve_quadratic(&f))
		return (0);
	*t = get_closest_intersection(f.t_1, f.t_2);
	return (*t > 0.0);
}



/*  ---------------- plan ----------------- */


t_vec	plane_normal(t_hit_info *hit)
{
	t_plane	*plane;

	plane = (t_plane *)(hit->obj->shape);
	return (plane->normal);
}

int	intersect_plane(t_ray *ray, void *shape, double *t, int *is_surface_hit)
{
	double	d;
	double	n_ray_dot;
	t_plane	*plane;

	(void)is_surface_hit;
	plane = (t_plane *)shape;
	n_ray_dot = dot(&(plane->normal), &(ray->dir));
	if (n_ray_dot == 0.0)
	{
		*t = 0;
		return (0);
	}
	d = dot(&(plane->normal), &(plane->point));
	*t = (d - dot(&(plane->normal), &(ray->origin))) / n_ray_dot;
	return (*t > 0.0);
}



/*  ----------------------------- cylindre -------------------  */

t_vec	cylinder_normal(t_hit_info *hit)
{
	t_cylinder	*cylinder;
	t_vec		projected;
	t_vec		center_to_hitpoint;

	cylinder = (t_cylinder *)(hit->obj->shape);
	if (!hit->is_surface_hit)
		return (cylinder->dir);
	center_to_hitpoint = sub(hit->hit_point, cylinder->center);
	projected = project(center_to_hitpoint, cylinder->dir);
	return (normalize(sub(center_to_hitpoint, projected)));
}

int	intersect_cylinder_covers(t_ray *ray, t_cylinder *cylinder, double *t,
	t_quadratic *f)
{
	double	t_1;
	double	t_2;

	intersect_plane(ray, (void *)&(cylinder->covers[0].plane), &t_1, NULL);
	intersect_plane(ray, (void *)&(cylinder->covers[1].plane), &t_2, NULL);
	*t = get_closest_intersection(t_1, t_2);
	return (*t > 0.0 && ((*t > f->t_1 && *t < f->t_2)
			|| (*t < f->t_1 && *t > f->t_2)));
}

int	intersect_cylinder_tube(t_ray *ray, t_cylinder *cylinder, t_quadratic *f)
{
	t_vec	w;
	double	dot_ray_dir_cyl_dir;
	double	dot_w_cylinder_dir;

	w = sub(ray->origin, cylinder->center);
	dot_ray_dir_cyl_dir = dot(&(ray->dir), &(cylinder->dir));
	dot_w_cylinder_dir = dot(&w, &(cylinder->dir));
	f->a = 1 - pow2(dot_ray_dir_cyl_dir);
	f->b = 2 * (dot(&(ray->dir), &w)
			- dot_ray_dir_cyl_dir * dot_w_cylinder_dir);
	f->c = dot(&w, &w) - pow2(dot_w_cylinder_dir) - pow2(cylinder->radius);
	return (solve_quadratic(f));
}

int	intersect_cylinder(t_ray *ray, void *shape, double *t, int *is_surface_hit)
{
	t_quadratic	f;
	t_cylinder	*cylinder;
	double		t_cover;

	cylinder = (t_cylinder *)shape;
	if (!intersect_cylinder_tube(ray, cylinder, &f))
		return (0);
	*t = get_closest_intersection(f.t_1, f.t_2);
	if (*t <= 0.0)
		return (0);
	cut_cylinder(ray, cylinder, t);
	if (intersect_cylinder_covers(ray, cylinder, &t_cover, &f))
		*t = get_closest_intersection(t_cover, *t);
	if (is_surface_hit != NULL)
		*is_surface_hit = *t != t_cover;
	return (*t > 0.0);
}






/*  -------------------- cone --------------------- */

t_vec	cone_normal(t_hit_info *hit)
{
	t_cone	*cone;
	t_vec	top_to_hitpoint_dir;
	t_vec	local_x_dir;

	cone = (t_cone *)(hit->obj->shape);
	if (!hit->is_surface_hit)
		return (cone->base.plane.normal);
	top_to_hitpoint_dir = sub(hit->hit_point, cone->top);
	local_x_dir = cross_product(&top_to_hitpoint_dir, &(cone->dir));
	return (cross_product(&local_x_dir, &top_to_hitpoint_dir));
}

int	cut_cone_surface(t_cone *cone, t_vec hit_point, double *t)
{
	t_vec	hit_to_center;
	double	projected_height;

	if (*t <= 0.0)
		return (0);
	hit_to_center = sub(hit_point, cone->center);
	projected_height = dot(&hit_to_center, &(cone->dir));
	if (projected_height <= cone->height && projected_height > 0.0)
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
	w = sub(ray->origin, cone->top);
	dot_ray_dir_h = dot(&(ray->dir), &(cone->dir));
	dot_w_h = dot(&w, &(cone->dir));
	dot_w_h_squared = pow2(dot_w_h);
	f->a = 1 - m * pow2(dot_ray_dir_h) - pow2(dot_ray_dir_h);
	f->b = 2 * (dot(&(ray->dir), &w) - m
			* dot_ray_dir_h * dot_w_h - dot_ray_dir_h * dot_w_h);
	f->c = dot(&w, &w) - m * dot_w_h_squared - dot_w_h_squared;
	return (solve_quadratic(f));
}

int	intersect_cone(t_ray *ray, void *shape, double *t, int *is_surface_hit)
{
	t_quadratic	f;
	t_cone		*cone;
	double		t_base;

	cone = (t_cone *)shape;
	if (!intersect_entire_cone(ray, cone, &f))
		return (0);
	if (dot(&(cone->dir), &(ray->dir)) >= 0)
	{
		*t = get_closest_intersection(f.t_1, f.t_2);
		cut_cone_surface(cone, get_ray_point(*ray, *t), t);
	}
	else
	{
		cut_cone_surface(cone, get_ray_point(*ray, f.t_1), &f.t_1);
		cut_cone_surface(cone, get_ray_point(*ray, f.t_2), &f.t_2);
		*t = get_closest_intersection(f.t_1, f.t_2);
	}
	intersect_circle(ray, (void *)&(cone->base), &t_base, NULL);
	*t = get_closest_intersection(*t, t_base);
	if (is_surface_hit != NULL)
		*is_surface_hit = *t != t_base;
	return (*t > 0.0);
}





/*  ------------------------------------------------------ */

double	get_closest_intersection(double t1, double t2)
{
	if (t1 <= 0.0 && t2 <= 0.0)
		return (0.0);
	if (t1 <= 0.0)
		return (t2);
	if (t2 <= 0.0)
		return (t1);
	if (t1 < t2)
		return (t1);
	return (t2);
}

int	intersect_objects(t_world *world, t_ray *ray, t_hit_info *hit)
{
	t_material	*objects;
	double		t;
	int			is_surface_hit;
	int			i;

	objects = world->objects;
	hit->t = INFINITY;
	is_surface_hit = 0;
	i = 0;
	while (i < world->nb_objects)
	{
		if (objects[i].intersect(ray, objects[i].shape, &t, &is_surface_hit)
			&& t < hit->t)
		{
			hit->t = t;
			hit->is_surface_hit = is_surface_hit;
			hit->obj = objects + i;
		}
		i++;
	}
	return (hit->t != INFINITY);
}