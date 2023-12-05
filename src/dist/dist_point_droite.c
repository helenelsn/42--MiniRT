/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dist_point_droite.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:36:14 by srapin            #+#    #+#             */
/*   Updated: 2023/12/05 22:38:38 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

double get_dist_droite_point(t_droite d, t_point p)
{
    double dist;
    dist = -1;
    if (get_v_norm(d.v))
        dist = get_v_norm(get_vec_from_point(d.p, p)) / get_v_norm(d.v);
    return dist;
}