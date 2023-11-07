/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dist_droite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:19:46 by srapin            #+#    #+#             */
/*   Updated: 2023/11/06 17:55:57 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

double get_dist_between_droite(t_droite d, t_droite e)
{
    t_vec_3d n;
    double dist;

    n = vec_x_vec_vectoriel(d.v, e.v);
    if (n.norm)
        dist =  vec_x_vec_scal(n, get_vec_from_point(d.p, e.p)) / n.norm;
    else
        dist = get_dist_droite_point(d, e.p);
    return dist;
}