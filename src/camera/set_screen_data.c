/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_screen_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 15:35:36 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/16 20:10:37 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/struct.h"
#include "../../inc/mini_rt.h"

void    set_screen_data(t_app *app)
{
    app->screen.image_width = fmax(1, IMAGE_WIDTH);
    app->screen.image_height = fmax(1, IMAGE_HEIGHT);
    app->screen.threads_amount = fmax(1, THREADS_NB);
    app->screen.aspect_ratio = app->screen.image_height \
        / app->screen.image_width;
    app->screen.pixels_per_thread = ( app->screen.image_width \
        *  app->screen.image_height) / app->screen.threads_amount;
}
