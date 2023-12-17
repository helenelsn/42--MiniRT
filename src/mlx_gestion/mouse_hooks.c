/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 18:22:41 by srapin            #+#    #+#             */
/*   Updated: 2023/12/17 01:26:13 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

t_hit_info	get_hit_info(t_app *app, t_point ray_origin, t_vec dir,
		int rebound_nb)
{
	t_ray	ray;
	t_vec	reflected_ray;
	t_color	local_color;
	double	reflected_color;

	ft_memset(&ray, 0, sizeof(t_ray));
	set_ray_infos(&ray, dir, ray_origin);
	no_tree_intersections(app, &ray, get_interval(HITPOINT_OFFSET, INFINITY));
	return (ray.hit_info);
}

int	handle_mouse(int keysym, int x, int y, t_app *app)
{
	t_point		pixel_center;
	t_hit_info	hit_info;

	set_pixel_center(app, &pixel_center, x, y);
	if (keysym == 1)
	{
		hit_info = get_hit_info(app, app->p_data.cam->p,
				get_directional_vect(app->p_data.cam->p,
					translate_point(pixel_center, pixel_sample(app, x, y))), 0);
		if (hit_info.distance > 0)
		{
			app->mlx_data.elem_selected = true;
			app->mlx_data.elem_hit = hit_info;
			print_elem_selected(app->mlx_data.mute,
				app->mlx_data.elem_hit.obj_type);
		}
	}
	else if (keysym == 3)
		deselect(app);
	return (keysym);
}
