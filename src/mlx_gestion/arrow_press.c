/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_press.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 01:35:12 by srapin            #+#    #+#             */
/*   Updated: 2023/12/17 01:35:57 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

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
		tmp.direction = vect_double_multiply(-1, tmp.direction);
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
}
