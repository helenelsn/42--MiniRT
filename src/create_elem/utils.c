/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 01:09:31 by srapin            #+#    #+#             */
/*   Updated: 2023/12/17 01:15:18 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

bool	ft_str_beggin_with(char *str, char *beg)
{
	return (ft_strnstr(str, beg, ft_strlen(beg)));
}

void	init_mat(t_material *mat)
{
	ft_bzero(mat, sizeof(t_material));
	mat->specular = -1;
	mat->textures.checkered = false;
	mat->textures.t = no_map;
	mat->reflective = 0;
}
