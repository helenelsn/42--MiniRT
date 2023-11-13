/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 02:23:05 by srapin            #+#    #+#             */
/*   Updated: 2023/11/13 16:21:05 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

void init_app(t_app *app)
{
    ft_bzero(&app, sizeof(t_app));
    app->mlx_data.mlx_ptr = mlx_init();
	if (!app->mlx_data.mlx_ptr)
		return;
		// return (EXIT_MLX_FAILURE);
	app->mlx_data.win_ptr = mlx_new_window(app->mlx_data.mlx_ptr, WINDOWS_WIDHT, WINDOWS_HEIGHT,
			"mimi-rt");
	if (!app->mlx_data.win_ptr)
	{
		close_mlx(app);
		return;
	}
}