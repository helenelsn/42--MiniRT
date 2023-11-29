/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_referentiel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 21:44:22 by hlesny            #+#    #+#             */
/*   Updated: 2023/11/29 00:16:53 by hlesny           ###   ########.fr       */
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
    if (fabs(vec_x_vec_scal((t_vec_3d){0, 1, 0}, cam->ref.z)) < 1.0)
        cam->ref.x = vec_x_vec_vectoriel((t_vec_3d){0, 1, 0}, cam->ref.z);
    else
        cam->ref.x = vec_x_vec_vectoriel((t_vec_3d){0, 0, 1}, cam->ref.z);
    cam->ref.y = vec_x_vec_vectoriel(cam->ref.z, cam->ref.x);
} */

