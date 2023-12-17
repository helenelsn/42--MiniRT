/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance_two_lines.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 16:06:00 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/17 04:10:11 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/mini_rt.h"

double	get_dist_between_droite(t_droite d, t_droite e)
{
	t_vec	n;
	double	dist;

	n = cross_product(d.v, e.v);
	if (n.norm)
		dist = dot(n, get_vec_from_point(d.p, e.p)) / n.norm;
	else
		dist = get_dist_droite_point(d, e.p);
	return (dist);
}
