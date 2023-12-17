/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 01:09:31 by srapin            #+#    #+#             */
/*   Updated: 2023/12/17 22:51:23 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt_bonus.h"

bool	ft_str_beggin_with(char *str, char *beg)
{
	return (ft_strnstr(str, beg, ft_strlen(beg)));
}

bool	ft_str_end_with(char *str, char *end)
{
	int	i;
	int	j;

	if (!end || !str)
		return (false);
	i = ft_strlen(str) -1;
	j = ft_strlen(end) -1;
	while (i >= 0 && j >= 0)
	{
		if (str[i] != end[j])
			return (false);
		j--;
		i--;
	}
	if (i == -1 && j >= 0)
		return (false);
	return (true);
}

void	init_mat(t_material *mat)
{
	ft_bzero(mat, sizeof(t_material));
	mat->specular = -1;
	mat->textures.checkered = false;
	mat->textures.t = no_map;
	mat->reflective = 0;
}
