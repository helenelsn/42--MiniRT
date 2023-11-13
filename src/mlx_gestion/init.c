/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 02:23:05 by srapin            #+#    #+#             */
/*   Updated: 2023/11/13 08:56:27 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	set_img(t_app *app)
{
	int		x;
	int		y;
	// t_img	*save_img;

	y = 0;
	while (y < WINDOWS_HEIGHT)
	{
		x = 0;
		while (x < WINDOWS_WIDHT)
		{
			my_mlx_pixel_put(&(app->image), x, y, x + y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(app->mlx_ptr, app->win_ptr, app->image.img, 0,
		0);
	// save_img = app->img;
	// app->img = app->back_img;
	// app->back_img = save_img;
}

void init_app(t_app *app)
{
    // ft_bzero(&app, sizeof(t_app));
	app->garbage = NULL;
	app->planes = NULL;
    app->mlx_ptr = mlx_init();
	// printf("1\n");
	if (!app->mlx_ptr)
		return;
		// return (EXIT_MLX_FAILURE);
	app->win_ptr = mlx_new_window(app->mlx_ptr, WINDOWS_WIDHT, WINDOWS_HEIGHT,
			"mimi-rt");
	app->image.img = mlx_new_image(app->mlx_ptr, WINDOWS_WIDHT, WINDOWS_HEIGHT);
	app->image.addr = mlx_get_data_addr(app->image.img, &(app->image.bpp),
			&(app->image.line_length), &(app->image.endian));
	// printf("2\n");
	if (!app->win_ptr)
	{
		// close_mlx(app);
		return;
	}
	set_img(app);
}