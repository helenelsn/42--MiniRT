/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 02:23:05 by srapin            #+#    #+#             */
/*   Updated: 2023/11/29 21:17:47 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*( int *)dst = color;
}

void	set_img(t_app *app)
{
	int		x;
	int		y;
	// t_img	*save_img;

	y = 0;
	while (y < IMAGE_HEIGHT)
	{
		x = 0;
		while (x < IMAGE_WIDTH)
		{
			my_mlx_pixel_put(&(app->mlx_data.image), x, y, x + y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(app->mlx_data.mlx_ptr, app->mlx_data.win_ptr, app->mlx_data.image.img, 0,
		0);
	// save_img = app->img;
	// app->img = app->back_img;
	// app->back_img = save_img;
}

// void init_app(t_app *app)
// {
//     ft_bzero(&app, sizeof(t_app));
//     app->mlx_data.mlx_ptr = mlx_init();
// 	if (!app->mlx_data.mlx_ptr)
// 		return;
// 		// return (EXIT_MLX_FAILURE);
// 	app->mlx_data.win_ptr = mlx_new_window(app->mlx_data.mlx_ptr, IMAGE_WIDTH, IMAGE_HEIGHT,
// 			"mimi-rt");
// 	if (!app->mlx_data.win_ptr)
// 	{
// 		// close_mlx(app);
// 		return;
// 	}
// 	set_img(app);
// }