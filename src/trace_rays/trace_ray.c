/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:27:01 by hlesny            #+#    #+#             */
/*   Updated: 2023/11/08 20:58:34 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/struct.h"
#include "../../inc/mini_rt.h"

/* Reflectiveness : assign a number between 0
 and 1 to every surface, specifying how reflective it is.
 Then we’ll compute the weighted average of the locally illuminated color 
 and the reflected color using that number as the weight. */


# define BACKGROUND_COLOR   255 // idk

// t_vec_3d    normal_to_vector(t_vec_3d u)
// {
    
// }

double diffuse_reflection_light_received()
{
    
}

double specular_reflection_light_received()
{
    
}

double entire_light_received()
{
    
}

void	img_pixel_put(t_image image, int x, int y, int color)
{
	char	*pixel;
	int		i;

    
	if (x < 0 || y < 0 || y > Y_WIN || x > X_WIN)
		return ;
	i = image.bpp - 8;
	pixel = image.addr + (y * image.line_length) + (x
			* (image.bpp / 8));
	*(int *)pixel = color;
	while (i >= 0)
	{
		if (image.endian)
			*(int *)pixel++ = (color >> i) & 0xFF;
		else
			*(int *)pixel++ = (color >> (image.bpp - 8 - i));
		i -= 8;
	}
}

t_vec_3d get_directional_vect(t_point_3d a, t_point_3d b)
{
    t_vec_3d u;

    u.x = b.x - a.x;
    u.y = b.y - a.y;
    u.z = b.z - a.z;
    u.norm = sqrt(pow(u.x, 2) + pow(u.y, 2) + pow(u.z, 2));
    return (u);
}

/* trace_ray() : given a ray, returns the color of the light coming from its direction*/

/* 
typedef struct  s_ray
{
    t_point_3d  origin; // camera position
    t_vec_3d    direction; // viewpoint - ray.origin
}               t_ray;              
*/
int    trace_ray(t_vlist *obj, double t_min, double t_max)
{
  
}

/* O represents the origin of the ray; 
although we’re tracing rays from the camera, 
which is placed at the origin, this won’t necessarily be the case in later stages, 
so it has to be a parameter. 
The same applies to t_min and t_max.
*/
void    compute_image(t_vlist *obj)
{
    int x;
    int y;
    

    x = - CW / 2;
    y = - CH / 2;
    while (x < CW / 2) // a modif car sinon doit recalculer a chaque passage et pas opti du tout
    {
        while (y < CH / 2)
        {
            t_point_2d u;
            u.x = x;
            u.y = y;
            img_pixel_put(image, canvas_to_screen(u), trace_ray(obj, ));
            y++;
        }
        x++;
    }
    /* put image to window */
}

/* -------------- Get normal vectors --------------- */

void    normalise(t_vec_3d *v)
{
    v->x /= v->norm;
    v->y /= v->norm;
    v->z /= v->norm;
    v->norm = 1;
}

t_vec_3d    normal_to_sphere(t_sphere sp, t_point_3d p)
{
    return (normalise(&get_directional_vect(sp.p, p)));
}

t_vec_3d normal_to_plane(t_plan pl, t_point_3d p)
{
    
}

t_vec_3d normal_to_cylinder(t_cylindre cy, t_point_3d p)
{
    
}

t_vec_3d normal_to_cone(t_cone cone, t_point_3d p)
{
    
}

// t_vec_3d normal_to_(, t_point_3d p)
// {
    
// }

// t_vec_3d normal_to_(, t_point_3d p)
// {
    
// }

// t_vec_3d normal_to_(, t_point_3d p)
// {
    
// }