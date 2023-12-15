/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_viewpoint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Helene <Helene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 20:04:36 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/15 18:35:42 by Helene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/struct.h"
#include "../../inc/mini_rt.h"

double  degrees_to_rad(double degrees)
{
    return (degrees * M_PI / 180.0);
}

void 	set_viewpoint_dimensions(t_app *app)
{
    // TODOOOOOO
    // Calculate the image height, and ensure that it's at least 1.
    //int image_height = static_cast<int>(image_width / aspect_ratio);
    //image_height = (image_height < 1) ? 1 : image_height;

    app->frame.width = FOCUS_DIST * tan(degrees_to_rad(app->p_data.cam->fov) * 0.5f) * 2; /* Width */
    app->frame.height = app->frame.width * app->aspect_ratio; /* Height */
}

// a tej car sinon sera dupliquee (car aussi utilisee dans la branche checkerboard, qui est pas encore merge)
static bool	ft_is_equalsf(const float a, const float b, const float tolerance)
{
	return ((a + tolerance >= b) && (a - tolerance <= b));
}

int ft_sign(double a)
{
    return ((a > 0.0) - (a < 0.0));
}

void    set_camera_ref(t_app *app)
{
    // Calculate the u,v,w unit basis vectors for the camera coordinate frame.
    app->p_data.cam->ref.w = vect_double_multiply(-1, app->p_data.cam->direction);
    normalise(&app->p_data.cam->ref.w);

    // a modif : pour l'instant l'axe X est inversé
    if (ft_is_equalsf(fabs(app->p_data.cam->direction.y), 1.f, DBL_EPSILON))
        app->p_data.cam->ref.u = cross_product((t_vec){0, 0, ft_sign(app->p_data.cam->direction.y)}, app->p_data.cam->ref.w);
    else
        app->p_data.cam->ref.u = cross_product((t_vec){0, 1, 0}, app->p_data.cam->ref.w);
    normalise(&app->p_data.cam->ref.u);
    
    app->p_data.cam->ref.v = cross_product(app->p_data.cam->ref.w, app->p_data.cam->ref.u);
    normalise(&app->p_data.cam->ref.v);
}


/*  Definit le referentiel de la camera (origine et base vectorielle)
    Calcule la position du pixel en haut a gauche du plan de projection
    Calcule les deux vecteurs directeurs des deux axes du plan de projection
    -> pourra ainsi calculer la position, dans le referentiel de base, de tous les pixels
     */
void    init_viewpoint(t_app *app)
{    
    t_vec    viewport_u;
    t_vec    viewport_v;
    t_vec    translate;
    t_point  viewp_upper_left;

    set_viewpoint_dimensions(app);

/* ----------------------------------*/

    // set_camera_ref(app);
    
    // Calculate the u,v,w unit basis vectors for the camera coordinate frame.
    app->p_data.cam->ref.w = vect_double_multiply(-1, app->p_data.cam->direction);
    normalise(&app->p_data.cam->ref.w);

    // a modif : pour l'instant l'axe X est inversé
    if (ft_is_equalsf(fabs(app->p_data.cam->direction.y), 1.f, DBL_EPSILON))
        app->p_data.cam->ref.u = cross_product((t_vec){0, 0, ft_sign(app->p_data.cam->direction.y)}, app->p_data.cam->ref.w);
    else
        app->p_data.cam->ref.u = cross_product((t_vec){0, 1, 0}, app->p_data.cam->ref.w);
    normalise(&app->p_data.cam->ref.u);
    
    app->p_data.cam->ref.v = cross_product(app->p_data.cam->ref.w, app->p_data.cam->ref.u);
    normalise(&app->p_data.cam->ref.v);


/* ----------------------------------*/

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    viewport_u = vect_double_multiply(app->frame.width, app->p_data.cam->ref.u);
    viewport_v = vect_double_multiply(- app->frame.height, app->p_data.cam->ref.v);
   
    // Calculate the horizontal and vertical delta vectors to the next pixel.
    app->frame.pixel_delta_u = vect_double_multiply(1.0/IMAGE_WIDTH, viewport_u);
    app->frame.pixel_delta_v = vect_double_multiply(1.0/IMAGE_HEIGHT, viewport_v);

    // Calculate the location of the upper left pixel.
    //  app->p_data.cam->p - (FOCUS_DIST * w) - viewport_u / 2 - viewport_v - 2;
    viewp_upper_left = translate_point(translate_point(translate_point(app->p_data.cam->p, 
        vect_double_multiply(- FOCUS_DIST, app->p_data.cam->ref.w)),
        vect_double_multiply(-1.0/2, viewport_u)), vect_double_multiply(-1.0/2, viewport_v)); 
    
    
    // pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    app->frame.pixel_00 = translate_point(viewp_upper_left,
        vect_double_multiply(0.5, vect_addition(app->frame.pixel_delta_u, app->frame.pixel_delta_v)));

    // Calculate the camera defocus disk basis vectors.
    //auto defocus_radius = focus_dist * tan(degrees_to_rad(defocus_angle / 2));
    //defocus_disk_u = u * defocus_radius;
    //defocus_disk_v = v * defocus_radius;
}