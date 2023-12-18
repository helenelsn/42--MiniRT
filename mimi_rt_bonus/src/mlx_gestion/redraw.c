/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 18:23:11 by srapin            #+#    #+#             */
/*   Updated: 2023/12/18 01:47:32 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt_bonus.h"

void	redraw(t_app *app)
{
	t_renderer	*threads;

	threads = init_threads(app);
	if (!threads)
		return ;
	launch_threads(threads);
	join_threads(threads);
	free(threads);
	mlx_put_image_to_window(app->mlx_data.mlx_ptr, app->mlx_data.win_ptr,
		app->mlx_data.image.img, 0, 0);
}
