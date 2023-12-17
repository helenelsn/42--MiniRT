/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_viewpoint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 20:04:36 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/17 04:54:00 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"
#include "../../inc/struct.h"

double	deg_to_rad(double degrees)
{
	return (degrees * M_PI / 180.0);
}

void	set_viewpoint_dimensions(t_app *app)
{
	app->frame.width = FOCUS_DIST * tan(deg_to_rad(app->p_data.cam->fov) * 0.5f)
		* 2;
	app->frame.height = app->frame.width * app->aspect_ratio;
}

int	sign(double a)
{
	return ((a > 0.0) - (a < 0.0));
}

void	set_camera_ref(t_app *app)
{
	app->p_data.cam->ref.w = vect_double_multiply(-1,
			app->p_data.cam->direction);
	normalise(&app->p_data.cam->ref.w);
	if (ft_is_equalsf(fabs(app->p_data.cam->direction.y), 1.f, DBL_EPSILON))
		app->p_data.cam->ref.u = cross_product((t_vec){0, 0,
				sign(app->p_data.cam->direction.y)}, app->p_data.cam->ref.w);
	else
		app->p_data.cam->ref.u = cross_product((t_vec){0, 1, 0},
				app->p_data.cam->ref.w);
	normalise(&app->p_data.cam->ref.u);
	app->p_data.cam->ref.v = cross_product(app->p_data.cam->ref.w,
			app->p_data.cam->ref.u);
	normalise(&app->p_data.cam->ref.v);
}

/*  Definit le referentiel de la camera (origine et base vectorielle)
    Calcule les deux vecteurs directeurs des deux axes du plan de projection
    Calcule la position du pixel en haut a gauche du plan de projection
       
	-> Calculate the vectors across the horizontal and down the 
    vertical viewport edges.
       
	-> Calculate the horizontal and vertical delta vectors to the next pixel.
    -> pourra ainsi calculer la position, dans le referentiel de base,
	de tous les pixels
     */
void	init_viewpoint(t_app *app)
{
	t_vec	viewport_u;
	t_vec	viewport_v;
	t_vec	translate;
	t_point	viewp_upper_left;

	set_viewpoint_dimensions(app);
	set_camera_ref(app);
	viewport_u = vect_double_multiply(app->frame.width, app->p_data.cam->ref.u);
	viewport_v = vect_double_multiply(-app->frame.height,
			app->p_data.cam->ref.v);
	app->frame.pixel_delta_u = vect_double_multiply(1.0 / IMAGE_WIDTH,
			viewport_u);
	app->frame.pixel_delta_v = vect_double_multiply(1.0 / IMAGE_HEIGHT,
			viewport_v);
	viewp_upper_left = translate_point(translate_point(translate_point(\
					app->p_data.cam->p, vect_double_multiply(-FOCUS_DIST,
						app->p_data.cam->ref.w)),
				vect_double_multiply(-1.0 / 2, viewport_u)),
			vect_double_multiply(-1.0 / 2, viewport_v));
	app->frame.pixel_00 = translate_point(viewp_upper_left,
			vect_double_multiply(0.5,
				vect_addition(app->frame.pixel_delta_u,
					app->frame.pixel_delta_v)));
}
