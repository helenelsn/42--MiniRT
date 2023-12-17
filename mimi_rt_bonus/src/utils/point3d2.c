/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point3d2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 02:47:33 by srapin            #+#    #+#             */
/*   Updated: 2023/12/17 22:51:23 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt_bonus.h"

t_point	double_to_point(double a)
{
	t_point	p;

	p.x = a;
	p.y = a;
	p.z = a;
	return (p);
}

void	reset_point(t_point *p, double a)
{
	p->x = a;
	p->y = a;
	p->z = a;
}

void	set_point(t_point *p, double x, double y, double z)
{
	p->x = x;
	p->y = y;
	p->z = z;
}

t_point	translate_point(t_point p, t_vec u)
{
	t_point	newp;

	newp.x = p.x + u.x;
	newp.y = p.y + u.y;
	newp.z = p.z + u.z;
	return (newp);
}
