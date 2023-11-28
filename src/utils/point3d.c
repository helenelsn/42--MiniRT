/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 00:36:39 by srapin            #+#    #+#             */
/*   Updated: 2023/11/28 18:13:26 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

bool	get_point(char *str, t_point_3d *p) //todo add args to raise error
{
	bool flag = true;
	char **sp;
	sp = ft_split(str, ',');
	if (!sp || null_term_tab_len((void **) sp) != 3)
		flag = false;
	else 
	{
        if (!ft_strisfloat(sp[0]) || !ft_strisfloat(sp[1]) || !ft_strisfloat(sp[2]))
            flag = false;
        p->x = atof(sp[0]);      
        p->y = atof(sp[1]);      
        p->z = atof(sp[2]);      
    }
	free_tab(sp);
	return flag;
}

/* ------- POINTS -------- */

t_point_3d	point_double_multiply(double n, t_point_3d a)
{
	t_point_3d b;

	b.x = n * a.x;
	b.y = n * a.y;
	b.z = n * a.z;
	return (b);
}

t_point_3d	point_addition(t_point_3d a, t_point_3d b)
{
	t_point_3d c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	return (c);
}

t_point_3d	point_substract(t_point_3d a, t_point_3d b)
{
	return (point_addition(a, point_double_multiply(-1, b)));
}
