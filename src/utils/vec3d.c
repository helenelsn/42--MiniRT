/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 00:48:26 by srapin            #+#    #+#             */
/*   Updated: 2023/10/19 00:52:49 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

bool	get_vec(char *str, t_vec_3d *p) //todo add args to raise error
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
			if (!ft_strisfloat(sp[i]) || -1 > ft_atof(str) || 1 < ft_atof(str))
				flag = false;
			i++;
		}
        p->x = ft_atof(sp[0]);      
        p->y = ft_atof(sp[1]);      
        p->z = ft_atof(sp[2]);
    }
	free_tab(sp);
	return flag;
}