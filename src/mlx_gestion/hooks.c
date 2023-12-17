/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 22:46:45 by srapin            #+#    #+#             */
/*   Updated: 2023/12/17 01:40:57 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

int	number_press(int keycode, t_app *app)
{
	if (!app->mlx_data.elem_selected)
		return (0);
	if (app->mlx_data.point_pushed)
		fill_double(keycode, &app->mlx_data.after_dot, true);
	else
		fill_double(keycode, &app->mlx_data.n, false);
}

bool	change_elem(t_app *app, double number)
{
	if (app->mlx_data.elem_selected && number
		&& app->mlx_data.elem_hit.obj_type == sphere)
		((t_sphere *)app->mlx_data.elem_hit.obj_content)->radius = number;
	else if (app->mlx_data.elem_selected && number
		&& app->mlx_data.elem_hit.obj_type == cylindre)
	{
		if (app->mlx_data.radius_or_heigt == 1)
			((t_cylindre *)app->mlx_data.elem_hit.obj_content)->radius = number;
		else if (app->mlx_data.radius_or_heigt == 2)
			((t_cylindre *)app->mlx_data.elem_hit.obj_content)->height = number;
		set_cylindre_dep((t_cylindre *)app->mlx_data.elem_hit.obj_content);
	}
	else if (app->mlx_data.elem_selected && number
		&& app->mlx_data.elem_hit.obj_type == cone)
	{
		if (app->mlx_data.radius_or_heigt == 1)
			((t_cone *)app->mlx_data.elem_hit.obj_content)->radius = number;
		else if (app->mlx_data.radius_or_heigt == 2)
			((t_cone *)app->mlx_data.elem_hit.obj_content)->height = number;
		set_cone_dep((t_cone *)app->mlx_data.elem_hit.obj_content);
	}
}

int	enter_press(int keycode, t_app *app)
{
	double	number;

	number = app->mlx_data.n + app->mlx_data.after_dot / 10;
	app->mlx_data.n = 0;
	app->mlx_data.after_dot = 0;
	if (!change_elem(app, number))
		return (0);
	redraw(app);
	return (0);
}

void	change_texture(int keycode, t_app *app)
{
	if (!app->mlx_data.elem_selected)
		return ;
	if (keycode == XK_c)
		app->mlx_data.elem_hit.obj_mat.textures.checkered = \
			!app->mlx_data.elem_hit.obj_mat.textures.checkered;
	else
	{
		if (app->mlx_data.elem_hit.obj_mat.textures.t == no_map)
			app->mlx_data.elem_hit.obj_mat.textures.t = 0;
		else
			app->mlx_data.elem_hit.obj_mat.textures.t += 1;
		app->mlx_data.elem_hit.obj_mat.textures.normap = \
			get_map_from_type(app->mlx_data.elem_hit.obj_mat.textures.t);
	}
	find_obj_and_replace_mat(app);
	redraw(app);
}

int	key_press(int keycode, t_app *app)
{
	if (keycode >= XK_0 && keycode <= XK_9)
		return (number_press(keycode, app));
	if (keycode == 46)
		app->mlx_data.point_pushed = true;
	if (keycode == XK_h && app->mlx_data.elem_selected
		&& (app->mlx_data.elem_hit.obj_type == cylindre
			|| app->mlx_data.elem_hit.obj_type == cone))
		app->mlx_data.radius_or_heigt = 2;
	if (keycode == XK_r && app->mlx_data.elem_selected
		&& (app->mlx_data.elem_hit.obj_type == cylindre
			|| app->mlx_data.elem_hit.obj_type == cone))
		app->mlx_data.radius_or_heigt = 1;
	if (keycode == 65293)
		enter_press(keycode, app);
	if (keycode == KEY_ESC)
		return (!close_mlx(app));
	if (keycode >= XK_Left && keycode <= XK_Down)
		arrow_press(keycode, app);
	if (keycode >= XK_w && keycode <= XK_z)
		modify_orientation(keycode, app);
	if (keycode == XK_m)
		app->mlx_data.mute = !app->mlx_data.mute;
	if (keycode == XK_c || keycode == XK_b)
		change_texture(keycode, app);
	return (0);
}
