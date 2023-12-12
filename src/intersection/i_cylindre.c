/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_cylindre.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Helene <Helene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 00:52:41 by srapin            #+#    #+#             */
/*   Updated: 2023/12/12 16:17:01 by Helene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"


// void    get_inter_for_cylindre(t_cylindre *c, t_droite d)
// {
//     //compute distance entre droites
//     t_droite c_dir;
//     double dist;

//     c_dir.p = c->p;
//     c_dir.v = c->vec;

//     dist = get_dist_between_droite(d, c_dir);

//     if (dist < 0 || dist > c->radius)
//         return ;// aucune intersection d' office;

//     // if  ->droite parrallele -> checker les disk

//     // else -> ????
//     //si dist > radius -> aucun
//     //si dist <= radius ->résoudre l'eq des 2 droites + calc les limites du cylindre
    
// }

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

int	intersect_plane(t_ray *ray, void *shape, double *t)
{
	double	d;
	double	n_ray_dot;
	t_plan	*plane;
    
	plane = (t_plan *) shape;
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
    // return (t != t_cover); 
        
    // t_cover = ft_min_and_positiv( get_inter_for_plan(&cy->cover_planes[0], (t_droite){r.origin, r.direction},&tmp), get_inter_for_plan(&cy->cover_planes[1], (t_droite){r.origin, r.direction},&tmp));
    // // if (t_cover == t)
    // //     printf("cover hit\n");
    
    // if (t_cover > 0.0 && ((t_cover > q.t_1 && t_cover < q.t_2) || (t_cover < q.t_1 && t_cover > q.t_2)))
    //     t = ft_min_and_positiv(t, t_cover);
    // // if (t != t_cover)
    // //     return -1;
    // return t;
     
	// intersect_plane(ray, (void *)&(cylinder->covers[1].plane), &t_2, NULL);
	// *t = get_closest_intersection(t_1, t_2);
	// *t = 0.0;
	// return (solve_quadratic(f));



    
    //compute distance entre droites
    
    // t_droite c_dir;
    // double dist;
    // t_vec dir = r.direction;
    // t_point pos = r.origin;
    // t_point center = cy->p;
    // double radius = cy->radius;
    
    // translate ray point with vec(cylinder_center to origin)
    // express ray point and ray directional vector in the cylinder base vectors
    // check for ray - cylinder intersection(s)
    // if any, express intersection point back to the initial base vectors
    // returns intersection point 

    

    // double a = (dir.x * dir.x) + (dir.z * dir.z);
    // double b = 2*(dir.x*(pos.x-center.x) + dir.z*(pos.z-center.z));
    // double c = (pos.x - center.x) * (pos.x - center.x) + (pos.z - center.z) * (pos.z - center.z) - (radius*radius);
    
    // double delta = b*b - 4*(a*c);
	// if(fabs(delta) < 0.001) return -1.0; 
    // if(delta < 0.0) return -1.0;
    
    // double f = (-b - sqrt(delta))/(2*a);
    // double g = (-b + sqrt(delta))/(2*a);
    // double t;
    
    // if (f>g) t = g;
    // else t = f;
    // return t;
    // double r = pos.y + t*dir.y;
    
    // if ((r >= center.y) && (r <= center.y + height))return t;
    // else return -1;













    // c_dir.p = cy->p;
    // c_dir.v = cy->vec;

    // dist = get_dist_between_droite(d, c_dir);

    // if (dist < 0 || dist > cy->radiusadius)
    //     return 0;// aucune intersection d' office;

    // n1ector n0 = normalize(crossProduct(cy->vec, (n1ector){1, 0, 0}));
    // n1ector n1 = crossProduct(cy->vec, n0);

    // Paramètres de l'équation quadratique
    // t_vec lol = get_directional_vect(r.origin , cy->p);
    // double a = dot(cy->n0, cy->n0) + dot(cy->n1, cy->n1);
    // double b = 2 * (dot(cy->n0, vec_minus_vec( lol,vect_double_multiply(  dot(lol, cy->vec), cy->vec ))) + dot(cy->n1, vec_minus_vec(lol , vect_double_multiply(dot(lol, cy->vec), cy->vec)    )));
    // double c = dot(     vec_minus_vec(   lol ,  vect_double_multiply(dot(lol, cy->vec), cy->vec ) ),  vec_minus_vec(lol , vect_double_multiply(dot(lol, cy->vec), cy->vec)) )- cy->radius * cy->radius * (dot(cy->n0, cy->n0) + dot(cy->n1, cy->n1));


    // double a = dot(cy->n0, cy->n0) + dot(cy->n1, cy->n1);
    // double b = 2 * (dot(cy->n0, vec_minus_vec( r.direction,vect_double_multiply(  dot(r.direction, cy->vec), cy->vec ))) + dot(cy->n1, vec_minus_vec(r.direction , vect_double_multiply(dot(r.direction, cy->vec), cy->vec)    )));
    // double c = dot(     vec_minus_vec(   r.direction ,  vect_double_multiply(dot(r.direction, cy->vec), cy->vec ) ),  vec_minus_vec(r.direction , vect_double_multiply(dot(r.direction, cy->vec), cy->vec)) )- cy->radius * cy->radius * (dot(cy->n0, cy->n0) + dot(cy->n1, cy->n1));

    // Discriminant de l'équation quadratique
    // double discriminant = b * b - 4 * a * c;

    // if (discriminant < 0) {
    //     // Pas d'intersection
    //     return 0;
    // } else {
    //     // Calcul des solutions de l'équation quadratique
    //     *t0 = (-b - sqrt(discriminant)) / (2 * a);
    //     *t1 = (-b + sqrt(discriminant)) / (2 * a);

    //     // cy->n1érifier que les solutions sont positives et dans la hauteur du cylindre
    //     // if ((*t1 >= 0 && *t1 <= cy->height) || (*t0 >= 0 && *t0 <= cy->height)) {
    //     if ((*t1 >= 0 ) || (*t0 >= 0)) {
    //         return 1;  // Intersection trouvée
    //     } else {
    //         return 0;  // Pas d'intersection dans la hauteur du cylindre
    //     }
    // }

    // t_vec n0;
    // t_vec n1;
    

    // double a =dot(n0, n0) + dot(n1, n1);
    // double b = 2 * (n0.x * (r.direction.x - cy->vec.x * dot(r.direction, cy->vec)) + n1.x * (r.direction.y - cy->vec.y * dot(r.direction, cy->vec)));
    // double c = (r.direction.x - cy->vec.x * dot(r.direction, cy->vec)) * (r.direction.x - cy->vec.x * dot(r.direction, cy->vec)) +
    //           (r.direction.y - cy->vec.y * dot(r.direction, cy->vec)) * (r.direction.y - cy->vec.y * dot(r.direction, cy->vec)) -
    //           cy->radiusadius * cy->radiusadius * (n0.x * n0.x + n1.x * n1.x);
    // // if  ->droite parrallele -> checker les disk

    // // else -> ????
    // // vec
    // //si dist > radius -> aucun
    // //si dist <= radius ->résoudre l'eq des 2 droites + calc les limites du cylindre
    // double discriminant = b * b - 4 * a * c;

    // if (discriminant < 0) {
    //     // Pas d'intersection
    //     return 0;
    // } else {
    //     // Calcul des solutions de l'équation quadratique
    //     *t1 = (-b - sqrt(discriminant)) / (2 * a);
    //     *t0 = (-b + sqrt(discriminant)) / (2 * a);

    //     // cy->n1érifier que les solutions sont positives et dans la hauteur du cylindre
    //     // if ((*t1 >= 0 && *t1 <= cy->height) || (*t0 >= 0 && *t0 <= cy->height)) {
    //     if ((*t1 >= 0) || (*t0 >= 0)) {
    //         // printf("heyy\n");
    //         return 1;  // Intersection trouvée
    //     } else {
    //         return 0;  // Pas d'intersection dans la hauteur du cylindre
    //     }
    // }
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
    // ray->hit_info.coef = get_inter_for_plan(p, d, &res);
    // if (!get_inter_for_cylindre(cy, d, &t0, &t1))
    // {
    //     return (false);
    // }
    if (!get_inter_for_cylindre(cy, *ray, &t))
        return false;
    ray->hit_info.coef  = t;
    if (ray->hit_info.coef <= 0)
        return false;
    // if (t0 < t1)
    //     ray->hit_info.coef =t0;
    // else 
    //     ray->hit_info.coef =t1;
    // else
    //     return false;
    res.x = ray->origin.x + ray->hit_info.coef * ray->direction.x;
    res.y = ray->origin.y + ray->hit_info.coef * ray->direction.y;
    res.z = ray->origin.z + ray->hit_info.coef * ray->direction.z;
    ray->hit_info.hit_point = res;
    ray->hit_info.distance = get_dist_between_points(ray->origin, ray->hit_info.hit_point);

    // printf("---------------------- intersected plan\n");

    return (true);
}