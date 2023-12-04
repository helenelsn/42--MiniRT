/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:40:29 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/03 16:49:39 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

/* static void	handle_keypress(t_data *data, int keycode)
{
	if (keycode == KEY_ORTHO)
		param_init(&data->maps, OG);
	if (keycode == KEY_ISO)
		param_init(&data->maps, ISO);
	if (keycode == KEY_Z_INCR || keycode == KEY_Z_DECR)
		set_altitude(data, keycode);
	if (keycode == KEY_L || keycode == KEY_R || keycode == KEY_U
		|| keycode == KEY_D || keycode == KEY_Q || keycode == KEY_W)
		set_angle(data, keycode);
	if (keycode == KEY_IN || keycode == KEY_OUT)
		set_zoom(data, keycode);
	if (keycode == KEY_RIGHT || keycode == KEY_LEFT || keycode == KEY_UP
		|| keycode == KEY_DOWN)
		translate(data, keycode);
} */

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