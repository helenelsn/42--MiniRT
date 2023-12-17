/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 00:36:39 by srapin            #+#    #+#             */
/*   Updated: 2023/12/17 22:51:23 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt_bonus.h"

bool	get_point(char *str, t_point *p)
{
	bool	flag;
	char	**sp;

	flag = true;
	sp = ft_split(str, ',');
	if (!sp || null_term_tab_len((void **)sp) != 3)
		flag = false;
	else
	{
		if (!ft_strisfloat(sp[0]) || !ft_strisfloat(sp[1])
			|| !ft_strisfloat(sp[2]))
			flag = false;
		p->x = atof(sp[0]);
		p->y = atof(sp[1]);
		p->z = atof(sp[2]);
	}
	free_tab(sp);
	return (flag);
}

/* ------- POINTS -------- */

t_point	point_double_multiply(double n, t_point a)
{
	t_point	b;

	b.x = n * a.x;
	b.y = n * a.y;
	b.z = n * a.z;
	return (b);
}

t_point	point_addition(t_point a, t_point b)
{
	t_point	c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	return (c);
}

t_point	point_substract(t_point a, t_point b)
{
	return (point_addition(a, point_double_multiply(-1, b)));
}
