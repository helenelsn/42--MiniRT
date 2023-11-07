/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 02:23:05 by srapin            #+#    #+#             */
/*   Updated: 2023/11/06 02:28:53 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

void init_app(t_app *app)
{
    
    ft_memset(app, 0, sizeof(t_app));
    app->mlx_ptr = mlx_init();
	if (!app->mlx_ptr)
		return (EXIT_MLX_FAILURE);
	app->win_ptr = mlx_new_window(app->mlx_ptr, WINDOWS_WIDHT, WINDOWS_HEIGHT,
			"mimi-rt");
	if (!app->win_ptr)
	{
		close_mlx(app);
		return (0);
	}
}