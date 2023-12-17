/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solving_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 03:42:53 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/17 03:52:02 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

double	pow2(double n)
{
	return (n * n);
}

t_point	get_ray_point(t_ray ray, double t)
{
	t_point	p;

	p.x = ray.origin.x + t * ray.direction.x;
	p.y = ray.origin.y + t * ray.direction.y;
	p.z = ray.origin.z + t * ray.direction.z;
	return (p);
}

double	ft_min(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}

double	ft_min_and_positiv(double a, double b)
{
	if (a <= 0 && b <= 0)
		return (0);
	if (a <= 0)
		return (b);
	if (b <= 0)
		return (a);
	return (ft_min(a, b));
}
