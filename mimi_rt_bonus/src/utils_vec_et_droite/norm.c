/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:07:56 by srapin            #+#    #+#             */
/*   Updated: 2023/12/17 22:51:23 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt_bonus.h"

double	get_v_norm(t_vec v)
{
	return (sqrt(dot(v, v)));
}

void	normalise(t_vec *v)
{
	v->norm = get_v_norm(*v);
	v->x /= v->norm;
	v->y /= v->norm;
	v->z /= v->norm;
	v->norm = 1;
}

t_vec	get_unitary_dir_vect(t_point a, t_point b)
{
	t_vec	u;

	u = get_directional_vect(a, b);
	normalise(&u);
	return (u);
}
