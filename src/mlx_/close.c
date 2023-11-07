/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 02:23:51 by srapin            #+#    #+#             */
/*   Updated: 2023/11/06 02:30:35 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

void close_mlx(t_app *app)
{
    if (!mlx_loop_end(app->mlx_ptr))
	{
		write(2, "Error when closing window\n", 26);
		mlx_destroy_window(app->mlx_ptr, app->win_ptr);
		return (0);
	}
	// mlx_destroy_image(app->mlx_ptr, app->img->img);
	// mlx_destroy_image(app->mlx_ptr, app->back_img->img);
	mlx_destroy_window(app->mlx_ptr, app->win_ptr);
	mlx_destroy_display(app->mlx_ptr);
	// free(app->mlx_ptr);
	// exit(0);
}