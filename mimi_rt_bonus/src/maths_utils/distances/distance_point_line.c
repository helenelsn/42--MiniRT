/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance_point_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 16:05:43 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/17 22:51:23 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/mini_rt_bonus.h"

double	get_dist_droite_point(t_droite d, t_point p)
{
	double	dist;

	dist = -1;
	if (get_v_norm(d.v))
		dist = get_v_norm(get_vec_from_point(d.p, p)) / get_v_norm(d.v);
	return (dist);
}
