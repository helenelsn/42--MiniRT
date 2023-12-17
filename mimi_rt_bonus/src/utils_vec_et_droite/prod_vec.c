/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prod_vec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:11:35 by srapin            #+#    #+#             */
/*   Updated: 2023/12/17 22:51:23 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt_bonus.h"

t_vec	cross_product(t_vec v, t_vec w)
{
	t_vec	u;

	u.x = v.y * w.z - v.z * w.y;
	u.y = v.z * w.x - v.x * w.z;
	u.z = v.x * w.y - v.y * w.x;
	u.norm = get_v_norm(u);
	return (u);
}
