/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance_two_points.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 16:05:23 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/16 16:06:28 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/mini_rt.h"

double get_dist_between_points(t_point p, t_point q)
{
    return get_v_norm(get_vec_from_point(p, q));
}