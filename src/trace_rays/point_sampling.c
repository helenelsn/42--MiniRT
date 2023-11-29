/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_sampling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:03:40 by hlesny            #+#    #+#             */
/*   Updated: 2023/11/29 00:27:34 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/struct.h"
#include "../../inc/mini_rt.h"

/* ------------------- UTILS ---------------- */

double degrees_to_radians(double degrees) {
    return (degrees * M_PI / 180.0);
}

double random_double() {
    // Returns a random real in [0,1).
    return (rand() / (RAND_MAX + 1.0));
}

double random_double_box(double min, double max) {
    // Returns a random real in [min,max).
    return (min + (max-min)*random_double());
}

int random_int(int min, int max) {
    // Returns a random integer in [min,max].
    return ((int)(random_double_box(min, max+1)));
}


/*  ------------------------------------------- */

t_point_3d  pixel_sample(t_app *app, int x, int y)
{
   /*  t_point_3d  pixel_center =  point_addition(point_addition(pixel_00, point_double_multiply(x, pixel_delta_u)),
                                point_double_multiply(y, pixel_delta_v));
    t_point_3d  pixel_sample = point_addition(pixel_center, pixel_sample()); */

    double      random_x;
    double      random_y;
    t_point_3d  sampled_p;
    
    random_x = -0.5 + random_double();
    random_y = -0.5 + random_double();
    sampled_p = translate_point(app->frame.pixel_00 ,vect_addition(vect_double_multiply(random_x, app->frame.pixel_delta_u),
        vect_double_multiply(random_y, app->frame.pixel_delta_v)));
    return (sampled_p);
}


