/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 00:36:39 by srapin            #+#    #+#             */
/*   Updated: 2023/10/19 00:43:38 by srapin           ###   ########.fr       */
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
        p->x = ft_atof(sp[0]);      
        p->y = ft_atof(sp[1]);      
        p->z = ft_atof(sp[2]);      
    }
	free_tab(sp);
	return flag;
}