/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 02:23:51 by srapin            #+#    #+#             */
/*   Updated: 2023/11/28 20:21:05 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

int close_mlx(void *arg)
{
	t_app *app = arg;
    if (!mlx_loop_end(app->mlx_data.mlx_ptr))
	{
		write(2, "Error when closing window\n", 26);
		mlx_destroy_window(app->mlx_data.mlx_ptr, app->mlx_data.win_ptr);
		return EXIT_FAILURE;
		// return (0);
	}
	mlx_destroy_image(app->mlx_data.mlx_ptr, app->mlx_data.image.img);
	mlx_destroy_window(app->mlx_data.mlx_ptr, app->mlx_data.win_ptr);
	// mlx_destroy_display(app->mlx_data.mlx_ptr); ->todo
	// exit(0);
	// printf("end of close mlx\n");
	return 0;
	// free(app->mlx_ptr);
	// exit(0);
}