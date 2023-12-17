/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 18:13:52 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/17 03:50:39 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"
#include "../../inc/struct.h"

/* ------- VECTORS -------- */

/* utile pour le ray traversal algorithm,
	dans lequel somme points et vecteurs */
t_point	get_vec_coord(t_vec v)
{
	t_point	p;

	p.x = v.x;
	p.y = v.y;
	p.z = v.z;
	return (p);
}

t_vec	vect_double_multiply(double n, t_vec a)
{
	t_vec	b;

	b.x = n * a.x;
	b.y = n * a.y;
	b.z = n * a.z;
	b.norm = get_v_norm(b);
	return (b);
}

t_vec	vect_addition(t_vec a, t_vec b)
{
	t_vec	c;

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

t_vec	get_directional_vect(t_point origin, t_point target)
{
	t_vec	u;

	u.x = target.x - origin.x;
	u.y = target.y - origin.y;
	u.z = target.z - origin.z;
	u.norm = sqrt(pow(u.x, 2) + pow(u.y, 2) + pow(u.z, 2));
	return (u);
}
