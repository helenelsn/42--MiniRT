/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:59:51 by Helene            #+#    #+#             */
/*   Updated: 2023/12/16 16:28:47 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/struct.h"
#include "../../../../inc/mini_rt.h"

/* Renvoie l'équivalent (2D) d'un point P (3D),
avec P positionné sur la surface d'un objet (sphère, plan, cylindre, cone)
Ceci, appelé "mapping" diffère selon la géométrie de l'objet 
-> calculates the UV coordinates for a hit position (P) on an object */



/*
The calculate_planar_map function calculates the UV coordinates for a hit position on a plane.
It first subtracts the position of the plane from the hit position to get a relative position.
If the plane's axis is not aligned with the Y-axis, it rotates the position to align with the Y-axis.
The U and V coordinates are then calculated as the modulus of the X and Z coordinates of the position, respectively
*/
t_point_2d   planar_mapping(t_plan *pl, t_point p)
{
    t_point_2d   uv;
    t_vec       position;

    position = rotate_relative_pos(pl->vec, p, pl->p);
        
	uv.u = fmodf_positive(position.x, 1.0); // modulof_positive()
	uv.v = fmodf_positive(position.z, 1.0);

	return (uv);
}

t_point_2d  cap_mapping(t_point p, t_vec surface_normal, t_point hit_point, double radius)
{
    t_point_2d  uv;
    t_vec       position;

    position = rotate_relative_pos(surface_normal, hit_point, p);
    uv.u = a_mod_b((position.x + radius) / (radius * 6), 1); // a_mod_b((position.x + radius) / (radius * 2), 1);
	uv.v = a_mod_b((position.z + radius) / (radius * 6), 1);
    return (uv);
}

t_point_2d   cylindrical_mapping(t_cylindre *cy, t_hit_info hit)
{
    t_point_2d  uv;
    t_vec       position;
    double      theta;
    double      raw_u;
      
    if (hit.cap_hit)
        return (cap_mapping(cy->p, cy->vec, hit.hit_point, cy->radius));
    
    position = rotate_relative_pos(cy->vec, hit.hit_point, cy->p);
    theta = atan2f(position.x / cy->radius,
			position.z / cy->radius);
	raw_u = theta / (float)(2.f * M_PI);
    
	uv.u = 1.f - (raw_u + 0.5f);
	uv.v = (0.5f + position.y / cy->height);        
    
    return (uv);
}

t_point_2d  conical_mapping(t_cone *co, t_hit_info hit)
{
    // if (hit.cap_hit)
        // return (cap_mapping(co->p, co->vec, hit.hit_point, co->radius));
    t_point_2d  uv;
    t_vec       position;
    double      theta;
    double      raw_u;
      
    if (hit.cap_hit)
        return (cap_mapping(co->p, co->vec, hit.hit_point, co->radius));
    
    position = rotate_relative_pos(co->vec, hit.hit_point, co->p);
    theta = atan2f(position.x / co->radius,
			position.z / co->radius);
	raw_u = theta / (float)(2.f * M_PI);
    
	uv.u = 1.f - (raw_u + 0.5f);
	uv.v = (0.5f + position.y / co->height);        
    
    return (uv);
    
}

t_point_2d  object_mapping(void *object, t_hit_info hit)
{
    if (hit.obj_type == sphere)
        return (spherical_mapping((t_sphere *)object, hit.hit_point));
    else if (hit.obj_type == plan)
        return (planar_mapping((t_plan *)object, hit.hit_point));
    else if (hit.obj_type == cylindre)
        return (cylindrical_mapping((t_cylindre *)object, hit));
    else // hit.obj_type == cone
        return (conical_mapping((t_cone *)object, hit));
}
