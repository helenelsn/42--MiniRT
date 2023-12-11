/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometric_mappings.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 20:25:29 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/11 15:25:39 by hlesny           ###   ########.fr       */
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
    
    theta = acos(- og_p.y);
    phi = atan2(- og_p.z, og_p.x) + M_PI;
    uv.u = phi / (2 * M_PI);
    uv.v = theta / M_PI;
    
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
t_point_2d cylindrical_map(t_point p)
{
    t_point_2d  uv;
    double      theta; // compute the azimuthal angle, same as with spherical_map()
    double      raw_u;

    theta = atan2(p.x, p.z);
    raw_u = theta / (2 * M_PI);
    uv.u = 1 - (raw_u + 0.5);
    
    // let v go from 0 to 1 between whole units of y
    uv.v = a_mod_b(p.y, 1);

    return (uv);
}

t_point_2d conical_map(t_point p)
{

}

t_point_2d  map_object(t_point p, t_type obj_type, void *content)
{
    t_point_2d  uv;
    
    if (obj_type == sphere)
        uv = spherical_map(p, (t_sphere *)content);
    else if (obj_type == cylindre)
        uv = cylindrical_map(p);
    else if (obj_type == plan)
        uv = planar_map(p);
    else // is a cone
        uv = (conical_map(p));
    
    return (uv);
}
