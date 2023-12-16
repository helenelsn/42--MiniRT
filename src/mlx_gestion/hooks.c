/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 22:46:45 by srapin            #+#    #+#             */
/*   Updated: 2023/12/15 19:38:18by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

int	handle_no_event(void)
{
	return (0);
}

int	fill_double(int keycode, double *to_mod, bool point_pushed)
{
	if (point_pushed)
		*to_mod /= 10;
	else
		*to_mod *= 10;
	*to_mod += keycode - XK_0;
}

int	number_press(int keycode, t_app *app)
{
	if (!app->mlx_data.elem_selected)
		return (0);
	if (app->mlx_data.point_pushed)
		fill_double(keycode, &app->mlx_data.after_dot, true);
	else
		fill_double(keycode, &app->mlx_data.n, false);
}

int	enter_press(int keycode, t_app *app)
{
	double	number;

	number = app->mlx_data.n + app->mlx_data.after_dot / 10;
	app->mlx_data.n = 0;
	app->mlx_data.after_dot = 0;
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
	else
		return (0);
	redraw(app);
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

void	up_down_arrow(int keycode, t_app *app)
{
	t_ray	tmp;
	t_point	*to_move;

	to_move = get_elem_point(app->mlx_data.elem_hit);
	if (!app->mlx_data.elem_selected)
		to_move = &app->p_data.cam->p;
	if (!to_move)
		return ;
	tmp.direction = app->mlx_data.orientation;
	if (keycode == XK_Down)
		tmp.direction = vect_double_multiply(-1, tmp.direction) ;
	tmp.origin = *to_move;
	normalise(&tmp.direction);
	*to_move = get_ray_point(tmp, 2);
}

void	left_right_arrow(int keycode, t_app *app)
{
	t_vec	*tmp;

	tmp = get_elem_vec(app->mlx_data.elem_hit);
	if (!app->mlx_data.elem_selected)
		tmp = &app->p_data.cam->direction;
	if (!tmp)
		return ;
	if (keycode == XK_Right)
		*tmp = vect_addition(*tmp, app->mlx_data.orientation);
	else if (keycode == XK_Left)
		*tmp = vect_substract(*tmp, app->mlx_data.orientation);
	normalise(tmp);
}

void	arrow_press(int keycode, t_app *app)
{
	if (!get_v_norm(app->mlx_data.orientation))
		return ;
	if (keycode == XK_Right || keycode == XK_Left)
		left_right_arrow(keycode, app);
	else
		up_down_arrow(keycode, app);
	set_coherence(app);
	redraw(app);
}

void	modify_orientation(int keycode, t_app *app)
{
	if (keycode == XK_w)
		app->mlx_data.orientation = (t_vec){0, 0, 0, 0};
	if (keycode == XK_x)
		app->mlx_data.orientation.x += 0.3;
	if (keycode == XK_y)
		app->mlx_data.orientation.y += 0.3;
	if (keycode == XK_z)
		app->mlx_data.orientation.z += 0.3;
	// printf("%s\n", __func__);
}

void	mute_demute(t_app *app)
{
	app->mlx_data.mute = !app->mlx_data.mute;
}

void find_obj_and_replace_mat( t_app *app)
{
	t_vlist *obj;
	void *to_find;

	if (!app->mlx_data.elem_selected)
		return;
	to_find = app->mlx_data.elem_hit.obj_content;
	if (app->mlx_data.elem_hit.obj_type == plan)
		obj = app->p_data.planes;
	else
		obj = app->p_data.objects;
	while(obj && obj->content != to_find)
	{
		obj = obj->next;
	}
	if (obj->content != to_find)
		return;

	obj->material = app->mlx_data.elem_hit.obj_mat;
}

void	change_texture(int keycode, t_app *app)
{
	if (!app->mlx_data.elem_selected)
		return ;
	if (keycode == XK_c)
		app->mlx_data.elem_hit.obj_mat.textures.checkered = !app->mlx_data.elem_hit.obj_mat.textures.checkered;
	else
	{
		if (app->mlx_data.elem_hit.obj_mat.textures.t == no_map)
			app->mlx_data.elem_hit.obj_mat.textures.t = 0;
		else
			app->mlx_data.elem_hit.obj_mat.textures.t += 1;
		app->mlx_data.elem_hit.obj_mat.textures.normap = get_map_from_type(app->mlx_data.elem_hit.obj_mat.textures.t);
	}

	// printf("hier %d, %d\n", app->mlx_data.elem_hit.obj_mat.textures.checkered, app->mlx_data.elem_hit.obj_mat.textures.t);
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

void	add_hooks(t_app *app)
{
	mlx_loop_hook(app->mlx_data.mlx_ptr, &handle_no_event, app);
	mlx_hook(app->mlx_data.win_ptr, 2, 1L << 0, key_press, app);
	mlx_hook(app->mlx_data.win_ptr, 33, 1L << 17, close_mlx, app);
	mlx_mouse_hook(app->mlx_data.win_ptr, &handle_mouse, app);
	mlx_loop(app->mlx_data.mlx_ptr); //ln (etait dans le main)
}