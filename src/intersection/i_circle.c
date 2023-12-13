/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_circle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 19:52:43 by srapin            #+#    #+#             */
/*   Updated: 2023/12/12 20:06:58 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

int	intersect_circle(t_ray *ray, t_circle circle, double *t)
{
	t_point		hit_point;

	if (!intersect_plane(ray, &circle.p, t))
		return (0);
	hit_point = get_ray_point(*ray, *t);
	if (get_v_norm(get_directional_vect(circle.center, hit_point)) <= circle.radius)
		return (1);
	*t = 0.0;
	return (0);
}
