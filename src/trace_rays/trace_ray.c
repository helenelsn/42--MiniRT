/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Helene <Helene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 00:04:46 by hlesny            #+#    #+#             */
/*   Updated: 2023/11/10 14:10:21 by Helene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/struct.h"
#include "../../inc/mini_rt.h"

typedef struct	s_hit_info
{
	// autre chose ?
	t_raytracing_material	obj_mat;
	double					distance; // ray_origin - object distance
}				t_hit_info;

typedef struct	s_ray
{
	t_point_3d	origin;
	t_vec_3d	direction;
}				t_ray;

/* ------------------------- UTILS ---------------------------- */

void    normalise(t_vec_3d *v)
{
    v->x /= v->norm;
    v->y /= v->norm;
    v->z /= v->norm;
    v->norm = 1;
}

t_vec_3d get_directional_vect(t_point_3d a, t_point_3d b)
{
    t_vec_3d u;

    u.x = b.x - a.x;
    u.y = b.y - a.y;
    u.z = b.z - a.z;
    u.norm = sqrt(pow(u.x, 2) + pow(u.y, 2) + pow(u.z, 2));
	normalise(&u);
    return (u);
}

/* ------------------ SCREEN - SCENE CONVERTIONS UTILS --------------- */

// tej les 3 une fois qu'a les singletons, juste pr que ca compile
# define DIST 1
# define VWP_H 1
# define VWP_W 1

/* Computes the height and width of the viewpoint, 
according to the field of view (FOV) parameter and the distance (arbitrary) */
void 	get_viewpoint_dimensions(float fov)
{
	double 	viewpoint_width;
	double	viewpoint_height;

    viewpoint_width = FOCUS_DIST * tan(fov * 0.5f * DEG_TO_RAD) * 2; /* Width */
    viewpoint_height = viewpoint_width * SCREEN_RATIO; /* Height */

    // set the viewpoint's height and width singletons 
}

/* Computes the position of the current pixel on the 
camera's projection plane (ie viewpoint) */
t_point_3d pixel_to_viewpoint_coord(int x, int y)
{
    t_point_3d v;

    v.x = VWP_W * (x / SCREEN_WIDTH);
    v.y = VWP_H * (y / SCREEN_HEIGHT);
    v.z = DIST;
    return (v);
}

/* canvas = centre au milieu (et non pas (0,0) en haut a gauche de l'ecran) */
t_point_2d  pixel_to_screen(t_point_2d c)
{
    t_point_2d s;

    s.x = SCREEN_WIDTH / 2 + c.x;
    s.y = SCREEN_HEIGHT / 2 - c.y;
    return (s);
}

/*  ---------------------- MAIN FUNCTIONS -------------------------- */

int 	get_pixel_color()
{
	
}

double 	get_received_light_intensity()
{
	
}

t_bsp_node	*get_corresponding_node()
{
	
}

void    trace_ray(t_app app, t_point_3d o)
{
    t_ray	ray;
	
	ray.origin = app.p_data.cam->p;
	ray.direction = get_directional_vect(ray.origin, o);
	/* get the corresponding bsp_node */
	/* check for intersections ray - objects in the current and children nodes */
	/* determine the closest intersection point's reflective ray's  direction */
	/* compute the received light (diffuse + specular + mood light) 
		-> use the total light intensity's computing formula */
	/* compute shadows, etc ? */
	/* ... */
	/* re-call the trace_ray function with the intersection point as origin,
		and the direction computed in the previous step
	 	-> repeat this 3 (REBOUNDS_NB) times, recursively */
	/* sum each get_pixel_color() return value from 
		each recursive call to get the final one ? */
	
	/* get the final pixel's color */
}

int		get_final_pixel_color(t_app app)
{
	t_point_3d	viewp = pixel_to_viewpoint_coord(x, y);
    trace_ray(app, viewp);
	
	
}

void    draw_scene(t_app app)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	// definir l'image
	while (y < WINDOWS_HEIGHT)
	{
		while (x < WINDOWS_WIDHT)
		{
			img_pixel_put(app.image, x, y, get_final_pixel_color(app, x, y));
			x++;
		}
		y++;
	}
}