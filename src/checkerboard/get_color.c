/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Helene <Helene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 18:29:52 by Helene            #+#    #+#             */
/*   Updated: 2023/12/10 19:37:35 by Helene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/struct.h"
#include "../../inc/mini_rt.h"

// retourner un pointeur plutot ?
t_checkers_func uv_checkers(double width, double height, t_color a, t_color b)
{
    t_checkers_func f;

    f.width = width;
    f.height = height;
    f.a = a;
    f.b = b;

    return (f);
}

t_color uv_pattern_at(t_checkers_func pattern, double u, double v)
{
    int coord;
    
    if (u < 0.0 || u > 1.0 || v < 0.0 || v > 1.0)
        ; // ?
    
    // le floor() est utile ? car est cast en int dans tous les cas
    coord = (floor(u * pattern.width) + floor(v * pattern.height));
    if (coord % 2)
        return (pattern.a);
    return (pattern.b);
}



/* convert the 3D point to spherical coordinates, 
then convert those spherical coordinates to a 2D point */
t_point_2d spherical_map(t_point p, t_sphere *sp)
{
    // t_vec   vec; // vec is the vector pointing from the sphere's origin (the world origin ?) to the point, which will also happen to be exactly equal to the sphere's radius.
    double      theta; // azimuthal angle. -π < theta <= π
    double      phi; // polar angle. 0 <= phi <= π
    double      raw_u;
    t_point_2d  uv;
    
    // vec = get_directional_vect(sp->p, p);
    theta = atan2(p.x, p.z); // Cette fonction renvoie la tangente inverse d'un angle y/x, où y = Opposite side of triangle et x = Adjacent side of triangle
    phi = acos(p.y / sp->radius);
    raw_u = theta / 2 * M_PI;
    uv.u = 1 - (raw_u + 0.5);
    uv.v = 1 - phi / M_PI;
    
    return (uv);
}



double  a_mod_b(double a, int b)
{
    double n;
    int c;

    n = 0;
    c = 0;
    while (n < a)
        (n += b * c++);
    
    return (sign(b) * fabs(a - (double)(--c * b)));
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
// !!!!!!!!!!!!!!! endcaps are not implemented yet (apparently has sthg to do with cube mapping?)
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


/* Note : 
If you want your checkers to look "square" on the sphere, be sure and set the width to twice the height. 
This is because of how the spherical map is implemented.
While both u and v go from 0 to 1, v maps 1 to π, but u maps 1 to 2π. */
t_color pattern_at(t_checkers_func f, t_point p, t_vlist *obj)
{
    t_point_2d  uv;
    
    if (obj->type == sphere)
        uv = spherical_map(p, (t_sphere *)obj->content);
    else if (obj->type == cylindre)
        uv = cylindrical_map(p);
    else if (obj->type == plan)
        uv = planar_map(p);
    else // is a cone
        uv = (conical_map(p));
        
    return (uv_pattern_at(f, uv.u, uv.v));
}
