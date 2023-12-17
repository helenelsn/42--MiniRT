/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 02:19:19 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/17 01:15:52 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/mini_rt.h"
#include "../../../../inc/struct.h"

t_point_2d	spherical_mapping(t_sphere *sp, t_point p)
{
	t_point_2d	uv;
	t_vec		position;
	double		theta;
	double		phi;
	double		raw_u;

	position = get_directional_vect(sp->p, p);
	theta = atan2f(position.x, position.z);
	phi = acosf(position.y / sp->radius);
	raw_u = theta / (2.f * M_PI);
	uv.u = raw_u + 0.5f;
	uv.v = phi / M_PI;
	return (uv);
}
