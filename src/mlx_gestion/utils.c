/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:51:47 by Helene            #+#    #+#             */
/*   Updated: 2023/12/16 21:36:38 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/mini_rt.h"

void deselect(t_app *app)
{
	app->mlx_data.point_pushed = false;
	app->mlx_data.n = 0;
	app->mlx_data.after_dot = 0;
	app->mlx_data.elem_selected = false;
	ft_bzero(&app->mlx_data.elem_hit, sizeof(t_hit_info));
	app->mlx_data.orientation = (t_vec) {0,0,0,0};
	app->mlx_data.radius_or_heigt = 0;
	if (!app->mlx_data.mute)
	printf("%s\n", __func__);
}