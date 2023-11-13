/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 02:23:51 by srapin            #+#    #+#             */
/*   Updated: 2023/11/13 16:21:17 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

void close_mlx(t_app *app)
{
    if (!mlx_loop_end(app->mlx_data.mlx_ptr))
	{
		write(2, "Error when closing window\n", 26);
		mlx_destroy_window(app->mlx_data.mlx_ptr, app->mlx_data.win_ptr);
		return;
		// return (0);
	}
	// mlx_destroy_image(app->mlx_data.mlx_ptr, app->mlx_data.img->img);
	// mlx_destroy_image(app->mlx_data.mlx_ptr, app->mlx_data.back_img->img);
	mlx_destroy_window(app->mlx_data.mlx_ptr, app->mlx_data.win_ptr);
	mlx_destroy_display(app->mlx_data.mlx_ptr);
	// free(app->mlx_data.mlx_ptr);
	// exit(0);
}