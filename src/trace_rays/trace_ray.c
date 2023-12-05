/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 00:04:46 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/05 22:38:56 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/struct.h"
#include "../../inc/mini_rt.h"


//todo
void	set_ray_infos(t_ray *ray, t_vec direction, t_point ray_origin)
{
	ray->origin = ray_origin;
	ray->direction = direction;
	
	normalise(&ray->direction); //tocheck
}


/*  ---------------------- todel, test sans arbre ---------------------- */

void	no_tree_intersections(t_parsing_data pdata, t_ray *ray, t_interval t)
{
    t_vlist     *obj;
    t_hit_info  *closest_obj;
    double 		min_dist;
	static int print;

    closest_obj = ft_calloc(sizeof(t_hit_info), 1);
    if (!closest_obj)
        return ;
    min_dist = t.max;
    
	obj = pdata.objects;
	while (obj)
    {
        if (intersect(obj, ray) && ray->hit_info.distance >= t.min
			&& ray->hit_info.distance <= min_dist)
        	{
        	    min_dist = ray->hit_info.distance;
				set_color_in_mat(obj->content, &obj->material, obj->type);
				set_specular_in_mat(obj->content, &obj->material, obj->type);
        	    copy_obj_properties(obj, closest_obj, ray->hit_info.hit_point);
			}
        obj = obj->next;
    }
	
	obj = pdata.planes;
	
	
	while (obj)
    {
		set_specular_in_mat(obj->content, &obj->material, obj->type);
		set_color_in_mat(obj->content, &obj->material, obj->type);
        if (intersect(obj, ray) && ray->hit_info.distance >= t.min
			&& ray->hit_info.distance < min_dist)
        	{
        	    min_dist = ray->hit_info.distance;
        	    copy_obj_properties(obj, closest_obj, ray->hit_info.hit_point);
				
        	}
        obj = obj->next;
    }
    

	// a modif : repetitif, moche
	
	
    if (min_dist < t.max)
    {
        // a verifier
        ray->hit_info = *closest_obj;
        ray->hit_info.distance = min_dist;
        return ;
    }
    ray->hit_info.distance = -1;
}

void 	update_ray_hit_infos(t_ray *ray)
{
	ray->hit_info.outward_normal = get_unit_normal(ray->hit_info, ray->hit_info.hit_point);
	ray->hit_info.reflected_ray = reflect_ray(ray->direction, ray->hit_info.outward_normal);
}

/*  --------------------------------------------------------------------- */

t_color    trace_ray(t_app *app, t_point ray_origin, t_vec dir, int rebound_nb)
{
    t_ray		ray;
	t_vec	reflected_ray;
	t_color 	local_color;
	double 		reflected_color;
	
	ft_memset(&ray, 0, sizeof(t_ray)); // verifier que ca ecrase pas de la data que veut garder (jpense pas)
	set_ray_infos(&ray, dir, ray_origin);
	
	//ray_traversal_algo(&app->root, &ray);
	no_tree_intersections(app->p_data, &ray, get_interval(HITPOINT_OFFSET, INFINITY));
	
	if (ray.hit_info.distance == -1) // le rayon n'intersecte aucun objet
	{
		// printf("love\n");
		return (app->background);
	}

	update_ray_hit_infos(&ray);
	
	local_color = color_scale(ray.hit_info.obj_mat.color, compute_lighting(app, ray.hit_info.obj_mat.specular, ray));
	if (local_color.hex != 65280 && local_color.hex != 32512 && local_color.hex != 65024)
	{
		printf("local_color = %u\n", local_color.hex);
	}
	


	
	//local_color = color_scale(ray.hit_info.obj_mat.color, compute_lighting(app, ray.hit_info.obj_mat.specular, ray));
	//local_color.hex =  ray.hit_info.obj_mat.color.hex * compute_lighting(app, ray.hit_info.obj_mat.specular, ray);
	
	/* get the final pixel's color */
	if (ray.hit_info.obj_mat.reflective <= 0 || rebound_nb == REBOUNDS_LIMIT)
		return (local_color);

	/* compute reflected color */
	//reflected_ray = get_incident_ray_of_light(vect_double_multiply(-1, ray.direction), ray.hit_info.outward_normal); // ou juste ray.direction en premier argument ?
	// reflected_color = trace_ray(app, ray.hit_info.hit_point, ray.hit_info.reflected_ray, rebound_nb + 1);
	
	// if (local_color * (1 - ray.hit_info.obj_mat.reflective) + reflected_color * ray.hit_info.obj_mat.reflective)

	// return (local_color * (1 - ray.hit_info.obj_mat.reflective) + reflected_color * ray.hit_info.obj_mat.reflective);
	return (local_color);
}

int		get_final_pixel_color(t_app *app, int x, int y)
{
	int 			sampling_count;
	t_color			pixel_color;
	t_point		pixel_center;
	t_point		viewp_pixel;
	t_color tmp;
	int r = 0;
	int g = 0;
	int b = 0;

	// pour sample SAMPLES_PER_PIXEL pixels et avoir une impression plus homogene
	sampling_count = 0;
	double defocus_angle = 0;

	ft_bzero(&pixel_color, sizeof(t_color)); 
	
	set_pixel_center(app, &pixel_center, x, y); // get coordinates of the pixel's center
	// pixel_color = trace_ray(app, app->p_data.cam->p, get_directional_vect(app->p_data.cam->p, viewp_pixel), 0);
	while (sampling_count < SAMPLES_PER_PIXEL)
	{
		viewp_pixel = translate_point(pixel_center, pixel_sample(app, x, y)) ;
		//printf("in %s, pixel = (%d, %d), sampled_coord = (%f, %f, %f)\n", __func__, x, y, viewp_pixel.x, viewp_pixel.y, viewp_pixel.z);
		tmp = trace_ray(app, app->p_data.cam->p, get_directional_vect(app->p_data.cam->p, viewp_pixel), 0);
		r += tmp.r;
		g += tmp.g;
		b += tmp.b;
		// pixel_color = color_add(pixel_color, trace_ray(app, app->p_data.cam->p, get_directional_vect(app->p_data.cam->p, viewp_pixel), 0));
		sampling_count++;
	}
	
	double inv =  SAMPLES_PER_PIXEL;	
	pixel_color.r = r / inv;
	pixel_color.g = g / inv;
	pixel_color.b = b / inv;
	
	// pixel_color = color_scale(pixel_color, inv); // ok ou va trop arrondir ?
	return (pixel_color.hex); 
}


void	img_pixel_put(t_image image, int x, int y, int color)
{
	char	*pixel;
	int		i;

    
	if (x < 0 || y < 0 || y > IMAGE_HEIGHT || x > IMAGE_WIDTH)
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
	while (y < IMAGE_HEIGHT) //while (y < IMAGE_HEIGHT -1)
	{
		x = 0;
		while (x < IMAGE_WIDTH) //while (x < IMAGE_WIDTH -1)
		{
			int color =  get_final_pixel_color(app, x, y);
			img_pixel_put(app->mlx_data.image, x, y, color);
			x++;
			// img_pixel_put(app->mlx_data.image, x+1, y, color);
			// img_pixel_put(app->mlx_data.image, x, y+1, color);
			// img_pixel_put(app->mlx_data.image, x+1, y+1, color);
			// x+=2;
		}
		// if (!(y % 100))
		// 	printf("endoffirstx, %d\n", y);
		// y +=2;
		y++;
	}
	
//	mlx_put_image_to_window(app->mlx_data.mlx_ptr, app->mlx_data.image.img, 0, 0);
}
