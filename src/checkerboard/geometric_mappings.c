/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometric_mappings.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Helene <Helene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 20:25:29 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/12 02:14:13 by Helene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/struct.h"
#include "../../inc/mini_rt.h"

/* convert the 3D point to spherical coordinates, 
then convert those spherical coordinates to a 2D point */
t_point_2d spherical_map(t_point p, t_sphere *sp)
{
    double      theta; // azimuthal angle. -π < theta <= π
    double      phi; // polar angle. 0 <= phi <= π
    double      raw_u;
    t_point_2d  uv;

    t_point     og_p = translate_point(p, get_directional_vect(sp->p, (t_point){0,0,0}));
    
    // theta = atan2(og_p.x, og_p.z); // Cette fonction renvoie la tangente inverse d'un angle y/x, où y = Opposite side of triangle et x = Adjacent side of triangle    
    // phi = acos(og_p.y / sp->radius);
    // raw_u = theta / 2 * M_PI;
    // uv.u = 1 - (raw_u + 0.5);
    // uv.v = 1 - phi / M_PI;
    
    // theta = acos(- og_p.y / sp->radius); // acos(- og_p.y)
    // phi = atan2(- og_p.z, og_p.x) + M_PI;
    // uv.u = phi / (2 * M_PI);
    // uv.v = theta / M_PI;

    
    
    return (uv);
}

// a tester
t_point_2d planar_map(t_point p)
{
    t_point_2d  uv;

    uv.u = a_mod_b(p.x, 1);
    uv.v = a_mod_b(p.z, 1);

    return (uv);
}


/* convert the 3D point to cylindrical coordinates, 
then convert those spherical coordinates to a 2D point */
// tocheck
// !!!!!! endcaps are not implemented yet (apparently has sthg to do with cube mapping?)
// t_point_2d cylindrical_map(t_hit_info hit)
// {
//     t_point_2d  uv;
//     double      theta; // compute the azimuthal angle, same as with spherical_map()
//     double      raw_u;

//     // t_point     og_p = translate_point(p, get_directional_vect(cy->p, (t_point){0,0,0}));
    
//     theta = atan2(hit.outward_normal.x, hit.outward_normal.z);
//     raw_u = theta / (2 * M_PI);
//     uv.u = 1 - (raw_u + 0.5);
//     // let v go from 0 to 1 between whole units of y
//     uv.v = a_mod_b(hit.outward_normal.y, 1);

//     return (uv);
// }

t_point_2d conical_map(t_point p)
{

}

// t_point_2d  map_object(t_hit_info hit)
// {
    // t_point_2d  uv;
    // 
    // if (obj_type == sphere)
        // uv = spherical_map(p, (t_sphere *)content);
    // else if (obj_type == cylindre)
        // uv = cylindrical_map(p, (t_cylindre *)content);
    // else if (obj_type == plan)
        // uv = planar_map(p);
    // else // is a cone
        // uv = (conical_map(p));
    // 
    // return (uv);
// }

float	get_angle(t_vec v, t_vec normalized)
{
	return (acosf(dot(v, normalized) / v.norm) * (180 / M_PI));
}

t_point_2d cylinder_map_body(t_hit_info hit, t_cylindre *cy)
{
    // t_vec2	point;
	float	height_from_base;
	t_vec	base_center_to_hit;
// 
	// point.x = get_angle(&(hit->normal), &(cylinder->system.x)) / 180 + 1;
	// point.x *= (dot(&(hit->normal), &(cylinder->system.z)) <= 0) * 2 - 1;
	// base_center_to_hit = sub(hit->hit_point, cylinder->covers->plane.point);
	// height_from_base = dot(&base_center_to_hit, &(cylinder->dir));
	// point.y = height_from_base / cylinder->height;
	// point.y *= 2 / (cylinder->circumference / cylinder->height);

    t_point_2d  uv;
    t_point     center_at_base;
    
    uv.u = get_angle(hit.outward_normal, cy->n1) / 180 + 1;
    uv.u *= (dot(hit.outward_normal, cy->n0) <= 0) * 2 - 1;
    
    // base_center_to_hit = get_directional_vect()
    center_at_base = translate_point(cy->p, vect_double_multiply(cy->height / 2, cy->vec));
    base_center_to_hit = get_directional_vect(center_at_base, hit.hit_point);
    height_from_base = dot(base_center_to_hit, cy->vec);

    uv.v = height_from_base / cy->height;
    // uv.v *= 2 / (cy->radius * 2 * M_PI/ cy->height);
    uv.v *= (cy->height / cy->radius * M_PI);
    
	return (uv);
}

t_point_2d  cylinder_map_cap(t_hit_info hit, t_cylindre *cy)
{
    // t_vec	center_to_hitpoint;
	// t_vec	hit_dir;
	// t_vec2	point;
// 
	// center_to_hitpoint = sub(*hitpoint, cylinder->center);
	// if (dot(&center_to_hitpoint, &(cylinder->dir)) < 0)
	// {
		// hit_dir = sub(center_to_hitpoint,
				// scale(cylinder->dir, cylinder->height / -2));
	// }
	// else
	// {
		// hit_dir = sub(center_to_hitpoint,
				// scale(cylinder->dir, cylinder->height / 2));
	// }
	// point.x = get_angle(&hit_dir, &(cylinder->system.x)) / 180 + 1;
	// point.x *= (dot(&hit_dir, &(cylinder->system.z)) <= 0) * 2 - 1;
	// point.y = 1 - (vec_len(hit_dir)) / cylinder->radius;
	// point.y /= cylinder->circumference / cylinder->radius / 2;
	// return (point);

    t_point_2d  uv;
    t_vec       center_to_p;
    t_vec       hit_dir;

    center_to_p = get_directional_vect(cy->p, hit.hit_point);
    if (dot(center_to_p, cy->vec) > 0.0)
    {
        hit_dir = vect_substract(center_to_p, vect_double_multiply(cy->height / 2, cy->vec));   
    }
    else
    {
        hit_dir = vect_substract(center_to_p, vect_double_multiply(cy->height / -2, cy->vec));
    }
    
    uv.u = get_angle(hit_dir, cy->n1) / 180 + 1;
    uv.u *= (dot(hit_dir, cy->n0) <= 0) * 2 - 1;
    
    uv.v = 1 - hit_dir.norm / cy->radius;
    // uv.v /= 2 * M_PI * cy->radius / cy->radius / 2;
    uv.v /= 4 * M_PI;
    
    return (uv);
    
}

t_point_2d  cylindrical_map(t_hit_info hit)
{
    t_cylindre *cy;

    cy = (t_cylindre *)hit.obj_content;
    // determine sur quelle surface du cylindre est le hit_point (contour ou caps)
    t_vec center_to_p = get_directional_vect(cy->p, hit.hit_point);
    
    // une des deux composantes selon n0 et n1 est < rayon -> p est sur le haut/bas 
    if (dot(center_to_p, cy->n0) < cy->radius || dot(center_to_p, cy->n1) < cy->radius)
        return (cylinder_map_cap(hit, cy));
    return (cylinder_map_body(hit, cy)); 
     
}

t_point_2d  map_object(t_hit_info hit)
{
    t_point_2d uv;
    
    if (hit.obj_type == sphere)
    {
        uv.u = atan2f(hit.outward_normal.z, hit.outward_normal.x) / M_PI + 1;
        uv.v = acosf(hit.outward_normal.y) / M_PI;
        
        // t_sphere *sp = hit.obj_content;
        // t_point     og_p = translate_point(hit.hit_point, get_directional_vect(sp->p, (t_point){0,0,0}));
        // uv.u = 0.5 + atan2(og_p.z, og_p.x) / (2 * M_PI);
        // uv.v = 0.5 - asin(og_p.y) / M_PI;
    }
    else if (hit.obj_type == cylindre)
    {
        uv = cylindrical_map(hit);
        // double theta = atan2(hit.outward_normal.x, hit.outward_normal.z);
        // double raw_u = theta / (2 * M_PI);
        // uv.u = 1 - (raw_u + 0.5);
        // uv.v = a_mod_b(hit.outward_normal.y, 1);

        // double theta = atan2(hit.hit_point.x, hit.hit_point.z);
        // double raw_u = theta / (2 * M_PI);
        // uv.u = 1 - (raw_u + 0.5);
        // uv.v = a_mod_b(hit.hit_point.y, 1);
    }
    return (uv);
}
