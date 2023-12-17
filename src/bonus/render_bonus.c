/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 23:34:15 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/17 05:26:09 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

void	*draw_scene_routine(void *routine_data)
{
	int			x;
	int			y;
	int			color;
	t_renderer	*r;

	r = (t_renderer *)routine_data;
	y = 0;
	while (y < IMAGE_HEIGHT)
	{
		x = r->id;
		while (x < IMAGE_WIDTH)
		{
			color = get_final_pixel_color(r->app, x, y);
			my_mlx_pixel_put(&r->app->mlx_data.image, x, y, color);
			x += THREADS_NB;
		}
		y++;
	}
	return (NULL);
}
