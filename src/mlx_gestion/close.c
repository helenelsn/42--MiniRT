/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 02:23:51 by srapin            #+#    #+#             */
/*   Updated: 2023/12/16 00:00:57 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

int close_mlx(void *arg)
{
	t_app *app = arg;
    if (!mlx_loop_end(app->mlx_data.mlx_ptr))
	{
		write(2, "Error when closing window\n", 26);
		mlx_destroy_window(app->mlx_data.mlx_ptr, app->mlx_data.win_ptr);
		return (EXIT_FAILURE);
		// return (0);
	}
	return 0;
}