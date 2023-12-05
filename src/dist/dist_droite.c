/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dist_droite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:19:46 by srapin            #+#    #+#             */
/*   Updated: 2023/12/05 22:38:56 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

double get_dist_between_droite(t_droite d, t_droite e)
{
    t_vec n;
    double dist;

    n = cross_product(d.v, e.v);
    if (n.norm)
        dist =  dot(n, get_vec_from_point(d.p, e.p)) / n.norm;
    else
        dist = get_dist_droite_point(d, e.p);
    return dist;
}