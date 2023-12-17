/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 23:32:08 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/17 05:26:01 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

void	redraw_bonus(t_app *app)
{
	t_renderer	*threads;

	threads = init_threads(app);
	if (!threads)
		return ;
	launch_threads(threads);
	join_threads(threads);
	free(threads);
}

int	minirt_get_started_bonus(t_app *app)
{
	t_renderer	*threads;

	if (initialise_mlx_data(app))
	{
		write(STDERR_FILENO, "Error : mlx initialisation.\n", 28);
		return (EXIT_MLX_FAILURE);
	}
	set_aspect_ratio(app);
	init_viewpoint(app);
	ft_bzero(&app->background, sizeof(t_color));
	threads = init_threads(app);
	if (!threads)
		return (EXIT_FAILURE);
	launch_threads(threads);
	join_threads(threads);
	free(threads);
	mlx_put_image_to_window(app->mlx_data.mlx_ptr, app->mlx_data.win_ptr,
		app->mlx_data.image.img, 0, 0);
	add_hooks(app);
	minirt_destroy_display(app);
	return (0);
}

// int	main(int argc, char **argv)
// {
	// t_app	app;
// 
	// ft_bzero(&app, sizeof(t_app));
	// parse(argc, argv, &app.p_data);
	// if (minirt_get_started_bonus(&app))
		// return (EXIT_MLX_FAILURE);
	// return (0);
// }
