/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Helene <Helene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:27:01 by hlesny            #+#    #+#             */
/*   Updated: 2023/10/21 00:46:32 by Helene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/struct.h"

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
    return (u);
}

double get_intersections(t_point_3d origin, t_point_3d p, t_vlist *obj)
{
    t_vec_3d l;
    t_type  type;

    l = get_directional_vect(origin, p);
    type = obj->type;
}

/* Avoir un tableau de tmin tmax correspondant à chaque forme geometrique */
int    trace_ray(t_vlist *obj, double t_min, double t_max)
{
    t_vlist *curr;
    double t;
    double t_temp;
    void *closest_shape;
    
    curr = obj;
    t = T_INF;
    t_temp = 0;
    closest_shape = NULL;
    while (curr)
    {
        
        /* creer un tableau de fonctions pour l'intersection du ray of light
        avec tel ou tel type de surface geometrique;
        accede directement a la fonction via tab_fct[type] 
        */
       /* peut avoir plusieurs intersections selon la forme géometrique,
          il faudra adapter ce code en conséquence */
        t_temp = get_intersection(obj);
        if (t_temp > t_min && t_temp < t_max && t_temp < t)
        {
            t = t_temp;
            closest_shape = obj->content;
        }
        curr = curr->next;
    }
    
    if (closest_shape == NULL)
        return (BACKGROUND_COLOR)
    return (closest_shape->color);
}

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