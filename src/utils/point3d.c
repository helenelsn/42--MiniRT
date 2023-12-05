/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 00:36:39 by srapin            #+#    #+#             */
/*   Updated: 2023/12/05 22:38:56 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

bool	get_point(char *str, t_point *p) //todo add args to raise error
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

t_point	point_double_multiply(double n, t_point a)
{
	t_point b;

	b.x = n * a.x;
	b.y = n * a.y;
	b.z = n * a.z;
	return (b);
}

t_point	point_addition(t_point a, t_point b)
{
	t_point c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	return (c);
}

t_point	point_substract(t_point a, t_point b)
{
	return (point_addition(a, point_double_multiply(-1, b)));
}

t_point double_to_point(double a)
{
    t_point p;
    
    p.x = a;
    p.y = a;
    p.z = a;
    return (p);
}

/* t_vec vectors_addition(t_vec u, t_vec v)
{
    t_vec w;

    w.x = u.x + v.x;
    w.y = u.y + v.y;
    w.z = u.z + v.z;
    
    return (w);
} */

void 	reset_point(t_point *p, double a)
{
	p->x = a;
	p->y = a;
	p->z = a;
}

void 	set_point(t_point *p, double x, double y, double z)
{
	p->x = x;
	p->y = y;
	p->z = z;
}

t_point  translate_point(t_point p, t_vec u)
{
    t_point  newp;

    newp.x = p.x + u.x;
    newp.y = p.y + u.y;
    newp.z = p.z + u.z;
    return (newp);
}
