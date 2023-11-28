/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 18:13:52 by hlesny            #+#    #+#             */
/*   Updated: 2023/11/28 18:14:17 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/struct.h"
#include "../../inc/mini_rt.h"

/* ------- VECTORS -------- */

/* utile pour le ray traversal algorithm, dans lequel somme points et vecteurs */
t_point_3d	get_vec_coord(t_vec_3d v)
{
	t_point_3d p;

	p.x = v.x;
	p.y = v.y;
	p.z = v.z;
	return (p);
}

t_vec_3d	vect_double_multiply(double n, t_vec_3d a)
{
	t_vec_3d b;

	b.x = n * a.x;
	b.y = n * a.y;
	b.z = n * a.z;
	b.norm = get_v_norm(b);
	return (b);
}

t_vec_3d	vect_addition(t_vec_3d a, t_vec_3d b)
{
	t_vec_3d c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	c.norm = get_v_norm(c);
	return (c);
}

t_vec_3d	vect_substract(t_vec_3d a, t_vec_3d b)
{
	return (vect_addition(a, vect_double_multiply(-1, b)));
}

void    normalise(t_vec_3d *v)
{
    v->x /= v->norm;
    v->y /= v->norm;
    v->z /= v->norm;
    v->norm = 1;
}

t_vec_3d	get_directional_vect(t_point_3d a, t_point_3d b)
{
    t_vec_3d u;

    u.x = b.x - a.x;
    u.y = b.y - a.y;
    u.z = b.z - a.z;
    u.norm = sqrt(pow(u.x, 2) + pow(u.y, 2) + pow(u.z, 2));
    return (u);
}

t_vec_3d	get_unitary_dir_vect(t_point_3d a, t_point_3d b)
{
	t_vec_3d u;

	u = get_directional_vect(a, b);
	normalise(&u);
	return (u);
}