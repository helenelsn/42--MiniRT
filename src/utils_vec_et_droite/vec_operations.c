/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 18:13:52 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/08 17:20:04 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/struct.h"
#include "../../inc/mini_rt.h"

/* ------- VECTORS -------- */

/* utile pour le ray traversal algorithm, dans lequel somme points et vecteurs */
t_point	get_vec_coord(t_vec v)
{
	t_point p;

	p.x = v.x;
	p.y = v.y;
	p.z = v.z;
	return (p);
}

t_vec	vect_double_multiply(double n, t_vec a)
{
	t_vec b;

	if (a.x)
		b.x = n * a.x;
	else
		b.x = 0.0;
	if (a.y)
		b.y = n * a.y;
	else
		b.y = 0.0;
	if (a.z)
		b.z = n * a.z;
	else
		b.z = 0.0;
	b.norm = get_v_norm(b);
	return (b);
}

t_vec	vect_addition(t_vec a, t_vec b)
{
	t_vec c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	c.norm = get_v_norm(c);
	return (c);
}

t_vec	vect_substract(t_vec a, t_vec b)
{
	return (vect_addition(a, vect_double_multiply(-1, b)));
}

void    normalise(t_vec *v)
{
    v->x /= v->norm;
    v->y /= v->norm;
    v->z /= v->norm;
    v->norm = 1;
}

t_vec	get_directional_vect(t_point origin, t_point target)
{
    t_vec u;

    u.x = target.x - origin.x;
    u.y = target.y - origin.y;
    u.z = target.z - origin.z;
    u.norm = sqrt(pow(u.x, 2) + pow(u.y, 2) + pow(u.z, 2));
    return (u);
}

t_vec	get_unitary_dir_vect(t_point a, t_point b)
{
	t_vec u;

	u = get_directional_vect(a, b);
	normalise(&u);
	return (u);
}