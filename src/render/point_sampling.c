/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_sampling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:03:40 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/16 15:49:51 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/struct.h"
#include "../../inc/mini_rt.h"

// Returns a random real in [0,1).
double random_double() {
    return (rand() / (RAND_MAX + 1.0));
}

void    set_pixel_center(t_app *app, t_point *pc, int x, int y)
{
    *pc = translate_point(app->frame.pixel_00, vect_addition(vect_double_multiply(x, app->frame.pixel_delta_u),
        vect_double_multiply(y, app->frame.pixel_delta_v)));
}

t_vec  pixel_sample(t_app *app, int x, int y)
{
    double      random_x;
    double      random_y;
    t_vec       sampled_p;
    
    random_x = - 0.5 + random_double();
    random_y = - 0.5 + random_double();
    sampled_p = vect_addition(vect_double_multiply(random_x, app->frame.pixel_delta_u),
        vect_double_multiply(random_y, app->frame.pixel_delta_v));
    return (sampled_p);
}
