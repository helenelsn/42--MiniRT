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


int fill_double(int keycode, double *to_mod, bool point_pushed)
{
	if (point_pushed)
		*to_mod /=10;
	else
		*to_mod *=10;
	*to_mod+= keycode - XK_0;
} 

int number_press(int keycode, t_app *app)
{
	if (!app->mlx_data.elem_selected)
		return (0);
	if (app->mlx_data.elem_hit.obj_type != sphere)
		return (0);
	if (app->mlx_data.point_pushed)
		fill_double(keycode, &app->mlx_data.after_dot, true);
	else
		fill_double(keycode, &app->mlx_data.n, false);
}


int	enter_press(int keycode, t_app *app)
{
	if (app->mlx_data.elem_selected && app->mlx_data.n)
		((t_sphere *) app->mlx_data.elem_hit.obj_content)->radius = app->mlx_data.n + app->mlx_data.after_dot/10;
	deselect(app);
	redraw(app);
}

void deselect(t_app *app)
{
	app->mlx_data.point_pushed = false;
	app->mlx_data.n = 0;
	app->mlx_data.after_dot = 0;
	app->mlx_data.elem_selected = false;
	ft_bzero(&app->mlx_data.elem_hit, sizeof(t_hit_info));
	app->mlx_data.orientation = (t_vec) {0,0,0,0};
}

void arrow_press_no_elem(int keycode, t_app *app)
{
	if (keycode == XK_Up)
		app->p_data.cam->direction.y += 0.1;
	else if (keycode == XK_Down)
		app->p_data.cam->direction.y -= 0.1;
	else if (keycode == XK_Right)
		app->p_data.cam->direction.x += 0.1;
	else if (keycode == XK_Left)
		app->p_data.cam->direction.x -= 0.1;
	normalise(&app->p_data.cam->direction);
	init_viewpoint(app);
}

void arrow_press_elem(int keycode, t_app *app)
{
	
	if (!get_v_norm(app->mlx_data.orientation))
		return;
	// if (keycode == XK_Up)
	// 	app->p_data.cam->direction.y += 0.1;
	// else if (keycode == XK_Down)
	// 	app->p_data.cam->direction.y -= 0.1;
	// else if (keycode == XK_Right)
	// 	app->p_data.cam->direction.x += 0.1;
	// else if (keycode == XK_Left)
	// 	app->p_data.cam->direction.x -= 0.1;
	// normalise(&app->p_data.cam->direction);
}

void arrow_press(int keycode, t_app *app)
{
	if (!app->mlx_data.elem_selected)
		arrow_press_no_elem(keycode, app);
	else
		arrow_press_elem(keycode, app);
	redraw(app);
}

void modify_orientation(int keycode, t_app * app)
{
	if (!app->mlx_data.elem_selected)
		return;
	app->mlx_data.orientation = (t_vec) {0,0,0,0};
	if (keycode == XK_x)	 
		app->mlx_data.orientation.x = 1;
	if (keycode == XK_y)	
		app->mlx_data.orientation.y  = 1;
	if (keycode == XK_z)	
		app->mlx_data.orientation.z  = 1;
	normalise(&app->mlx_data.orientation);
	
}

void mute_demute(t_app *app)
{
	app->mlx_data.mute = !app->mlx_data.mute;
}

int	key_press(int keycode, t_app *app)
{
	if (keycode >=XK_0 && keycode <= XK_9)
		return number_press(keycode, app);
	if (keycode == XK_p)
		app->mlx_data.point_pushed = true;
	if (keycode == XK_e) //todo trouver le keysim du enter
		enter_press(keycode, app); 
	if (keycode == KEY_ESC)
		return (!close_mlx(app));
	if (keycode >= XK_Left && keycode <= XK_Down)
		arrow_press(keycode, app);
	if (keycode >= XK_x && keycode <= XK_z)
		modify_orientation(keycode, app);
	if (keycode >= XK_m)
		app->mlx_data.mute = !app->mlx_data.mute;
    return (0);
}

void	add_hooks(t_app *app)
{
	mlx_loop_hook(app->mlx_data.mlx_ptr, &handle_no_event, app);
	mlx_hook(app->mlx_data.win_ptr, 2, 1L << 0, key_press, app);
	mlx_hook(app->mlx_data.win_ptr, 33, 1L << 17, close_mlx, app);
	mlx_mouse_hook(app->mlx_data.win_ptr, &handle_mouse, app);
}