/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 00:36:39 by srapin            #+#    #+#             */
/*   Updated: 2023/11/29 00:35:38 by hlesny           ###   ########.fr       */
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

t_point_3d double_to_point(double a)
{
    t_point_3d p;
    
    p.x = a;
    p.y = a;
    p.z = a;
    return (p);
}

/* t_vec_3d vectors_addition(t_vec_3d u, t_vec_3d v)
{
    t_vec_3d w;

    w.x = u.x + v.x;
    w.y = u.y + v.y;
    w.z = u.z + v.z;
    
    return (w);
} */

void 	reset_point(t_point_3d *p, double a)
{
	p->x = a;
	p->y = a;
	p->z = a;
}

void 	set_point(t_point_3d *p, double x, double y, double z)
{
	p->x = x;
	p->y = y;
	p->z = z;
}

t_point_3d  translate_point(t_point_3d p, t_vec_3d u)
{
    t_point_3d  newp;

    newp.x = p.x + u.x;
    newp.y = p.y + u.y;
    newp.z = p.z + u.z;
    return (newp);
}
