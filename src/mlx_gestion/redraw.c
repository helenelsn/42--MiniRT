/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 18:23:11 by srapin            #+#    #+#             */
/*   Updated: 2023/12/16 22:42:23 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

void redraw(t_app *app)
{
    //draw_scene_routine((void *)app); // a modiffff
	mlx_put_image_to_window(app->mlx_data.mlx_ptr, app->mlx_data.win_ptr,
        app->mlx_data.image.img, 0, 0);
    // printf("redr\n", __func__);
}
