/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 00:04:46 by hlesny            #+#    #+#             */
/*   Updated: 2023/11/28 21:57:04 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/struct.h"
#include "../../inc/mini_rt.h"


//todo
void	set_ray_infos(t_ray *ray, t_vec_3d direction, t_point_3d ray_origin)
{
	ray->origin = ray_origin;
	ray->direction = direction;	
}


int    trace_ray(t_app *app, t_point_3d ray_origin, t_vec_3d dir, int rebound_nb)
{
    t_ray		ray;
	t_vec_3d	reflected_ray;
	double 		local_color;
	double 		reflected_color;
	
	ft_memset(&ray, 0, sizeof(t_ray)); // verifier que ca ecrase pas de la data que veut garder (jpense pas)
	set_ray_infos(&ray, dir, ray_origin);
	
	ray_traversal_algo(&app->root, &ray);
	if (ray.hit_info.distance == -1) // le rayon n'intersecte aucun objet
		return (BACKGROUND_COLOR); 
	
	// a mettre directement dans test_intersections() ?
	ray.hit_info.hit_p_normal = get_unit_normal(ray.hit_info, ray.hit_info.hit_point);

	//???? c'est pas plutot "get_incident_ray_of_light(ray.direction, ray.hit_info.hit_p_normal)"" ?
	//ray.hit_info.reflected_ray = get_directional_vect(ray.hit_info.hit_point, ray.origin); // essayer avec -ray.direction et voir si donne les memes resultats
	
	ray.hit_info.reflected_ray = get_incident_ray_of_light(vect_double_multiply(-1, ray.direction), ray.hit_info.hit_p_normal); // ou juste ray.direction en premier argument ?
	
	local_color = ray.hit_info.obj_mat.color * compute_lighting(app, ray.hit_info.obj_mat.specular, ray);
	
	/* get the final pixel's color */
	if (ray.hit_info.obj_mat.reflective <= 0 || rebound_nb == RECURS_LIMIT)
		return (local_color);

	/* compute reflected color */
	//reflected_ray = get_incident_ray_of_light(vect_double_multiply(-1, ray.direction), ray.hit_info.hit_p_normal); // ou juste ray.direction en premier argument ?
	reflected_color = trace_ray(app, ray.hit_info.hit_point, ray.hit_info.reflected_ray, rebound_nb + 1);
	
	return (local_color * (1 - ray.hit_info.obj_mat.reflective) + reflected_color * ray.hit_info.obj_mat.reflective);
}

int		get_final_pixel_color(t_app *app, int x, int y)
{
	// return (x+y);
	int sampling_count;
	int	pixel_color = 0;

	sampling_count = 0;
	double defocus_angle = 0; // pour sample SAMPLES_PER_PIXEL pixels et avoir une impression plus homogene
	// implementer les fonctions pour generer des samples de pixels dans [pixel - epsilon, pixel + epsilon]

	t_point_3d	viewp = pixel_to_viewpoint_coord(x, y);
	// t_point_3d test = {0, 0, 0};
	// while (sampling_count < SAMPLES_PER_PIXEL)
	// pixel_color += trace_ray(app, app->p_data.cam->p, get_directional_vect(app->p_data.cam->p, viewp), 0);
	// return pixel_color;
	while (sampling_count < SAMPLES_PER_PIXEL)
	{
		
		//get sampled pixel
    	pixel_color += trace_ray(app, app->p_data.cam->p, get_directional_vect(app->p_data.cam->p, viewp), 0);
		sampling_count++;
	}
    //pixel_color = trace_ray(app, app->p_data.cam->p, get_directional_vect(app->p_data.cam->p, viewp), 0);
	return (pixel_color / SAMPLES_PER_PIXEL); // ok ou va trop arrondir ?
}

void	img_pixel_put(t_image image, int x, int y, int color)
{
	char	*pixel;
	int		i;

    
	if (x < 0 || y < 0 || y > WINDOWS_HEIGHT || x > WINDOWS_WIDHT)
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

void    draw_scene(t_app *app)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	// definir l'image
	while (y < WINDOWS_HEIGHT)
	{
		x = 0;
		while (x < WINDOWS_WIDHT)
		{
			img_pixel_put(app->mlx_data.image, x, y, get_final_pixel_color(app, x, y));
			x++;
		}
		// if (!(y % 100))
		// 	printf("endoffirstx, %d\n", y);
		y++;
	}
	
	printf("end\n");
}
