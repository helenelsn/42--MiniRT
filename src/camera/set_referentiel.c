/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_referentiel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 21:44:22 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/05 22:38:56 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/struct.h"
#include "../../inc/mini_rt.h"

/* void    set_basis_vectors(t_camera *cam)
{
    cam->ref.origin = cam->p;
   
    cam->ref.z = cam->direction;
    normalise(&cam->ref.z);
   
    // determines if cam->dir equals to u_y from the base referentiel
    // si dot = 1 -> les deux vecteurs sont egaux : leur produit vectoriel donnera un vecteur nul
    if (fabs(dot((t_vec){0, 1, 0}, cam->ref.z)) < 1.0)
        cam->ref.x = cross_product((t_vec){0, 1, 0}, cam->ref.z);
    else
        cam->ref.x = cross_product((t_vec){0, 0, 1}, cam->ref.z);
    cam->ref.y = cross_product(cam->ref.z, cam->ref.x);
} */

