/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:55:20 by srapin            #+#    #+#             */
/*   Updated: 2023/12/18 00:43:41 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mini_rt.h"

int	initialise_mlx_data(t_app *app)
{
	app->mlx_data.mlx_ptr = mlx_init();
	if (!app->mlx_data.mlx_ptr)
		return (EXIT_MLX_FAILURE);
	app->mlx_data.win_ptr = mlx_new_window(app->mlx_data.mlx_ptr, IMAGE_WIDTH,
			IMAGE_HEIGHT, "miniRT");
	if (!app->mlx_data.win_ptr)
	{
		mlx_destroy_display(app->mlx_data.mlx_ptr);
		free(app->mlx_data.mlx_ptr);
		return (EXIT_MLX_FAILURE);
	}
	app->mlx_data.image.img = mlx_new_image(app->mlx_data.mlx_ptr, IMAGE_WIDTH,
			IMAGE_HEIGHT);
	app->mlx_data.image.addr = mlx_get_data_addr(app->mlx_data.image.img,
			&(app->mlx_data.image.bpp),
			&(app->mlx_data.image.line_length),
			&(app->mlx_data.image.endian));
	return (0);
}

static int	minirt_get_started(t_app *app)
{
	if (initialise_mlx_data(app))
	{
		write(STDERR_FILENO, "Error : mlx initialisation.\n", 28);
		return (EXIT_MLX_FAILURE);
	}
	set_aspect_ratio(app);
	init_viewpoint(app);
	ft_bzero(&app->background, sizeof(t_color));
	draw_scene(app);
	mlx_put_image_to_window(app->mlx_data.mlx_ptr, app->mlx_data.win_ptr,
		app->mlx_data.image.img, 0, 0);
	add_hooks(app);
	minirt_destroy_display(app);
	return (0);
}

int	main(int argc, char **argv)
{
	t_app	app;

	ft_bzero(&app, sizeof(t_app));
	parse(argc, argv, &app.p_data);
	if (app.p_data.err)
		minirt_destroy_display(&app);
	if (minirt_get_started(&app))
		return (EXIT_MLX_FAILURE);
	return (0);
}
