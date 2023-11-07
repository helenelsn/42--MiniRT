/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 00:48:26 by srapin            #+#    #+#             */
/*   Updated: 2023/11/06 17:35:30 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

bool	get_vec_from_str(char *str, t_vec_3d *p) //todo add args to raise error
{
	bool flag = true;
	char **sp;
	sp = ft_split(str, ',');
	if (!sp || null_term_tab_len((void **) sp) != 3)
		flag = false;
	else 
	{
        int i = 0;
        while(i < 3)
		{
			if (!ft_strisfloat(sp[i]) || -1 > atof(str) || 1 < atof(str))
				flag = false;
			i++;
		}
        p->x = atof(sp[0]);      
        p->y = atof(sp[1]);      
        p->z = atof(sp[2]);
    }
	free_tab(sp);
	p->norm = get_v_norm(*p);
	return flag;
}

t_vec_3d get_vec_from_point(t_point_3d p, t_point_3d q)
{
	t_vec_3d v;

	v.x = p.x- q.x;
	v.y = p.y- q.y;
	v.z = p.z- q.z;
	v.norm = get_v_norm(v);
	return v;
}