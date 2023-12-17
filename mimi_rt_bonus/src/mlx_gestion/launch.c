/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 08:57:45 by srapin            #+#    #+#             */
/*   Updated: 2023/12/17 22:51:23 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt_bonus.h"

int	handle_no_event(void)
{
	return (0);
}

void	add_hooks(t_app *app)
{
	mlx_loop_hook(app->mlx_data.mlx_ptr, &handle_no_event, app);
	mlx_hook(app->mlx_data.win_ptr, 2, 1L << 0, key_press, app);
	mlx_hook(app->mlx_data.win_ptr, 33, 1L << 17, close_mlx, app);
	mlx_mouse_hook(app->mlx_data.win_ptr, &handle_mouse, app);
	mlx_loop(app->mlx_data.mlx_ptr);
}

void	launch_app(t_app *app)
{
	add_hooks(app);
	mlx_loop(app->mlx_data.mlx_ptr);
}
