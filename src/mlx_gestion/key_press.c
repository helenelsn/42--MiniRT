/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:40:29 by hlesny            #+#    #+#             */
/*   Updated: 2023/11/28 20:04:49 by srapin           ###   ########.fr       */
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
    
    (void)app;
	/* erase_and_new_img(data);
	handle_keypress(data, keycode);
	draw_map(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->image.img, 0,
		0); */
	
    return (0);
}