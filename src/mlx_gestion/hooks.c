/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 22:46:45 by srapin            #+#    #+#             */
/*   Updated: 2023/12/05 22:51:27 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

int	handle_no_event(void)
{
	return (0);
}

int	key_press(int keycode, t_app *app)
{
	if (keycode == KEY_ESC)
	{
		if (close_mlx(app))
			return (EXIT_MLX_FAILURE);
			
		// if (!mlx_loop_end(app->mlx_data.mlx_ptr))
		// {
		// 	write(2, "Error when closing window\n", 26);
		// 	return (EXIT_MLX_FAILURE);
		// }
		return (EXIT_SUCCESS);
	}
    
	else if (keycode == XK_Up)
	{
		printf("up push\n");
		// app->
		//bouger plutot la camera
		app->p_data.cam->direction.y += 0.1;
		// app->frame.pixel_00.y += 0.5;
	}
	else if (keycode == XK_Down)
		app->p_data.cam->direction.y -= 0.1;
	else if (keycode == XK_Right)
		app->p_data.cam->direction.x += 0.1;
	// 	// app->y_offset -= 0.2 / app->zoom;
	else if (keycode == XK_Left)
		app->p_data.cam->direction.x -= 0.1;
	// 	// app->keycode += 0.2 / app->zoom;
		// app->frame.pixel_00.y -= 0.5;
	init_viewpoint(app);
	draw_scene(app);
	mlx_put_image_to_window(app->mlx_data.mlx_ptr, app->mlx_data.win_ptr,
        app->mlx_data.image.img, 0, 0);
		// app->y_offset += 0.2 / app->zoom;
	// else if (keycode == XK_Down)
	// 	// app->y_offset -= 0.2 / app->zoom;
	// else if (keycode == XK_Left)
	// 	// app->keycode += 0.2 / app->zoom;
	// else if (keysym == XK_Right)
	// 	// app->keycode -= 0.2 / app->zoom;
    (void)app;
	/* erase_and_new_img(data);
	handle_keypress(data, keycode);
	draw_map(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->image.img, 0,
		0); */
	
    return (0);
}


int	handle_mouse(int keysym, int x, int y, t_app *app)
{
	t_point		viewp_pixel;
	t_point		pixel_center;
	t_hit_info		hit_info;
	

	set_pixel_center(app, &pixel_center, x, y);
	if (keysym == 1) // && app->fract == JULIA)
	{
		viewp_pixel = translate_point(pixel_center, pixel_sample(app, x, y)) ;
		//printf("in %s, pixel = (%d, %d), sampled_coord = (%f, %f, %f)\n", __func__, x, y, viewp_pixel.x, viewp_pixel.y, viewp_pixel.z);
		hit_info = get_hit_info(app, app->p_data.cam->p, get_directional_vect(app->p_data.cam->p, viewp_pixel), 0);
		if (hit_info.distance > 0)
			printf("object hit\n");
			if (hit_info.obj_type == sphere)
				resize_sphere(app, hit_info);
			if (hit_info.obj_type == cylindre)
				resize_cylindre(app, hit_info);
	}
	return (keysym);
}

void	add_hooks(t_app *app)
{
	mlx_loop_hook(app->mlx_data.mlx_ptr, &handle_no_event, app);
	mlx_hook(app->mlx_data.win_ptr, 2, 1L << 0, key_press, app);
	mlx_hook(app->mlx_data.win_ptr, 33, 1L << 17, close_mlx, app);
	mlx_mouse_hook(app->mlx_data.win_ptr, &handle_mouse, app);
	// mlx_hook(app->mlx_data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, app);
	// mlx_hook(app->mlx_data.win_ptr, 33, 1L << 17, &close_mlx, app);
	// mlx_mouse_hook(app->mlx_data.win_ptr, &handle_mouse, app);
}