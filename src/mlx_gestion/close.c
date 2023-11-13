/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 02:23:51 by srapin            #+#    #+#             */
/*   Updated: 2023/11/13 09:06:15 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

int close_mlx(void *arg)
{
	t_app *app = arg;
    if (!mlx_loop_end(app->mlx_ptr))
	{
		write(2, "Error when closing window\n", 26);
		mlx_destroy_window(app->mlx_ptr, app->win_ptr);
		return 0;
		// return (0);
	}
	// mlx_destroy_image(app->mlx_ptr, app->img->img);
	// mlx_destroy_image(app->mlx_ptr, app->back_img->img);
	mlx_destroy_window(app->mlx_ptr, app->win_ptr);
	mlx_destroy_display(app->mlx_ptr);
	return 0;
	// free(app->mlx_ptr);
	// exit(0);
}