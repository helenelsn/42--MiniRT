/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:51:47 by Helene            #+#    #+#             */
/*   Updated: 2023/12/17 22:51:23 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt_bonus.h"

void	deselect(t_app *app)
{
	app->mlx_data.point_pushed = false;
	app->mlx_data.n = 0;
	app->mlx_data.after_dot = 0;
	app->mlx_data.elem_selected = false;
	ft_bzero(&app->mlx_data.elem_hit, sizeof(t_hit_info));
	app->mlx_data.orientation = (t_vec){0, 0, 0, 0};
	app->mlx_data.radius_or_heigt = 0;
}

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || y > IMAGE_HEIGHT || x > IMAGE_WIDTH)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(int *)dst = color;
}

int	fill_double(int keycode, double *to_mod, bool point_pushed)
{
	if (point_pushed)
		*to_mod /= 10;
	else
		*to_mod *= 10;
	*to_mod += keycode - XK_0;
	return (0);
}

void	set_coherence(t_app *app)
{
	if (app->mlx_data.elem_selected && app->mlx_data.elem_hit.obj_type == cone)
		set_cone_dep((t_cone *)app->mlx_data.elem_hit.obj_content);
	if (app->mlx_data.elem_selected
		&& app->mlx_data.elem_hit.obj_type == cylindre)
		set_cylindre_dep((t_cylindre *)app->mlx_data.elem_hit.obj_content);
	if (app->mlx_data.elem_selected && app->mlx_data.elem_hit.obj_type == plan)
		set_eq((t_plan *)app->mlx_data.elem_hit.obj_content);
	if (!app->mlx_data.elem_selected)
		init_viewpoint(app);
}

void	find_obj_and_replace_mat(t_app *app)
{
	t_vlist	*obj;
	void	*to_find;

	if (!app->mlx_data.elem_selected)
		return ;
	to_find = app->mlx_data.elem_hit.obj_content;
	if (app->mlx_data.elem_hit.obj_type == plan)
		obj = app->p_data.planes;
	else
		obj = app->p_data.objects;
	while (obj && obj->content != to_find)
	{
		obj = obj->next;
	}
	if (obj->content != to_find)
		return ;
	obj->material = app->mlx_data.elem_hit.obj_mat;
}
