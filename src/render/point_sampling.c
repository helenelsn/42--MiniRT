/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_sampling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:03:40 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/17 02:04:33 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"
#include "../../inc/struct.h"

// Returns a random real in [0,1).
double	random_double(void)
{
	return (rand() / (RAND_MAX + 1.0));
}

void	set_pixel_center(t_app *app, t_point *pc, int x, int y)
{
	*pc = translate_point(app->frame.pixel_00,
			vect_addition(vect_double_multiply(x,
					app->frame.pixel_delta_u),
				vect_double_multiply(y,
					app->frame.pixel_delta_v)));
}

t_vec	pixel_sample(t_app *app)
{
	double	random_x;
	double	random_y;
	t_vec	sampled_p;

	random_x = -0.5 + random_double();
	random_y = -0.5 + random_double();
	sampled_p = vect_addition(vect_double_multiply(random_x,
				app->frame.pixel_delta_u),
			vect_double_multiply(random_y, app->frame.pixel_delta_v));
	return (sampled_p);
}
