/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Helene <Helene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:38:52 by Helene            #+#    #+#             */
/*   Updated: 2023/11/22 15:44:26 by Helene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/struct.h"
#include "../../inc/mini_rt.h"
#include "../../inc/bsp.h"

void	destroy_and_free(t_app app)
{
	mlx_destroy_image(app.mlx_data.mlx_ptr, app.mlx_data.image.img);
	mlx_destroy_window(app.mlx_data.mlx_ptr, app.mlx_data.win_ptr);
	mlx_destroy_display(app.mlx_data.mlx_ptr);
	free(app.mlx_data.mlx_ptr);
	exit(0);
}