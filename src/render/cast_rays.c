/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 00:04:46 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/17 02:04:45 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"
#include "../../inc/struct.h"

void	set_ray_infos(t_ray *ray, t_vec direction, t_point ray_origin)
{
	ray->origin = ray_origin;
	ray->direction = direction;
	normalise(&ray->direction);
}

t_color	trace_ray(t_app *app, t_point ray_origin, t_vec dir, int rebound_nb)
{
	t_ray	ray;
	t_color	local_color;
	t_vec	reflected_ray;
	t_color	reflected_color;

	ft_memset(&ray, 0, sizeof(t_ray));
	set_ray_infos(&ray, dir, ray_origin);
	no_tree_intersections(app, &ray, get_interval(HITPOINT_OFFSET, INFINITY));
	if (ray.hit_info.distance == -1 || !ray.hit_info.obj_content)
	// le rayon n'intersecte aucun objet
		return (app->background);
	ray.hit_info.reflected_ray = reflect_ray(ray.direction,
			ray.hit_info.outward_normal);
	local_color = compute_lighting(app, ray);
	if (ray.hit_info.obj_mat.reflective <= 0 || rebound_nb == REBOUNDS_LIMIT)
		return (local_color);
	/* compute reflected color */
	// A VERIFIER !!!!!!!!!!!
	// reflected_ray = reflect_ray(ray.direction, ray.hit_info.outward_normal);
		// ou juste ray.direction en premier argument ?
	// reflected_ray = get_incident_ray_of_light(vect_double_multiply(-1,
				//ray.direction), ray.hit_info.outward_normal);
		// ou juste ray.direction en premier argument ?
	reflected_color = trace_ray(app, ray.hit_info.hit_point,
			ray.hit_info.reflected_ray, rebound_nb + 1);
	return (color_add(color_scale(local_color, 1
				- ray.hit_info.obj_mat.reflective), color_scale(reflected_color,
				ray.hit_info.obj_mat.reflective)));
}

int	get_final_pixel_color(t_app *app, int x, int y)
{
	int		sampling_count;
	t_color	pixel_color;
	t_point	pixel_center;
	t_point	viewp_pixel;
	t_color	tmp;
	int		r;
	int		g;
	int		b;
	double	inv;

	r = 0;
	g = 0;
	b = 0;
	sampling_count = 0;
	ft_bzero(&pixel_color, sizeof(t_color));
	set_pixel_center(app, &pixel_center, x, y);
	while (sampling_count < SAMPLES_PER_PIXEL)
	{
		viewp_pixel = translate_point(pixel_center, pixel_sample(app));
		//tmp = color_add (tmp, trace_ray(app, app->p_data.cam->p,
					//get_directional_vect(app->p_data.cam->p, viewp_pixel), 0));
		tmp = trace_ray(app, app->p_data.cam->p,
				get_directional_vect(app->p_data.cam->p, viewp_pixel), 0);
		r += tmp.r;
		g += tmp.g;
		b += tmp.b;
		sampling_count++;
	}
	inv = SAMPLES_PER_PIXEL;
	pixel_color.r = r / inv;
	pixel_color.g = g / inv;
	pixel_color.b = b / inv;
	// pixel_color = color_scale(pixel_color, 1.0 / SAMPLES_PER_PIXEL);
	return (pixel_color.hex);
}

void	img_pixel_put(t_image image, int x, int y, int color)
{
	char	*pixel;
	int		i;

	if (x < 0 || y < 0 || y > IMAGE_HEIGHT || x > IMAGE_WIDTH)
		return ;
	i = image.bpp - 8;
	pixel = image.addr + (y * image.line_length) + (x * (image.bpp / 8));
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

void	draw_scene(t_app *app)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < IMAGE_HEIGHT)
	{
		x = 0;
		while (x < IMAGE_WIDTH)
		{
			color = get_final_pixel_color(app, x, y);
			my_mlx_pixel_put(&app->mlx_data.image, x, y, color);
			x++;
		}
		y++;
	}
}
