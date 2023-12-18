/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 00:48:26 by srapin            #+#    #+#             */
/*   Updated: 2023/12/18 02:51:07 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt_bonus.h"

bool	get_vec_from_str(char *str, t_vec *p)
{
	bool	flag;
	char	**sp;
	int		i;

	sp = ft_split(str, ',');
	flag = true;
	if (!sp || null_term_tab_len((void **)sp) != 3)
		flag = false;
	else
	{
		i = 0;
		while (i < 3)
		{
			if (!ft_strisfloat(sp[i]) || -1 > atof(sp[i]) || 1 < atof(sp[i]))
				flag = false;
			i++;
		}
		p->x = atof(sp[0]);
		p->y = atof(sp[1]);
		p->z = atof(sp[2]);
	}
	free_tab(sp);
	p->norm = get_v_norm(*p);
	return (flag);
}

t_vec	get_vec_from_point(t_point p, t_point q)
{
	t_vec	v;

	v.x = p.x - q.x;
	v.y = p.y - q.y;
	v.z = p.z - q.z;
	v.norm = get_v_norm(v);
	return (v);
}
