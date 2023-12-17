/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 19:17:45 by srapin            #+#    #+#             */
/*   Updated: 2023/12/17 19:52:13 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

bool	set_checkerboard(t_material *mat, char *info)
{
	if (!info || (ft_strlen(info) < 2) ||  (!ft_strisequal(info, "ch") && !ft_strisequal(info, "ch\n")))
		return (false);
	mat->textures.checkered = true;
	return (true);
}

bool 	ft_str_end_with(char *str, char *end)
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

bool	set_bump_map_type(t_material *mat, char *info)
{
	if ((ft_strlen(info) < 3) || !info || !ft_str_beggin_with(info, "b=") 
		|| (ft_strlen(info) == 4 && !ft_str_end_with(info, "\n")) ) //|| ft_strlen(info) < 3 || ft_strlen(info) > 4)
		return (false);
	if (info[2] == 'c')
		mat->textures.t = cliff;
	else if (info[2] == 's')
		mat->textures.t = sand;
	else if (info[2] == 't')
		mat->textures.t = terrain;
	else if (info[2] == 'a')
		mat->textures.t = tree;
	else if (info[2] == 'w')
		mat->textures.t = wood;
	else
		return (false);
	mat->textures.normap = get_map_from_type(mat->textures.t);
	return (true);
}

bool	set_reflective(char *str, double *to_mod)
{
	if (!str)
		return (true);
	if ((ft_strlen(str) < 3) || (!ft_strisfloat(str + 3) && !ft_strisint(str + 3))
		|| !ft_str_beggin_with(str, "re="))
		return (false);
	*to_mod = atof(str + 3);
	if (*to_mod < 0.0 || *to_mod > 1.0)
		return (false);
	return (true);
}

bool	set_specular(char *str, double *to_mod)
{
	if (!str)
		return (true);
	if (((ft_strlen(str) < 3) || !ft_strisfloat(str + 3) && !ft_strisint(str + 3))
		|| !ft_str_beggin_with(str, "sp="))
		return (false);
	*to_mod = atof(str + 3);
	if (*to_mod < 0)
		return (false);
	return (true);
}

bool	set_bonus_options(t_material *mat, char **tab)
{
	int		size;
	bool	flag;
	int		i;

	flag = true;
	i = 0;
	size = null_term_tab_len((void **)tab);
	while (i < size)
	{
		if (tab[i] && tab[i][0] != '\n')
		{
			flag = set_reflective(tab[i], &mat->reflective);
			flag = (flag || set_specular(tab[i], &mat->specular));
			flag = (flag || set_bump_map_type(mat, tab[i]));
			flag = (flag || set_checkerboard(mat, tab[i]));
		}
		i++;
	}
	return (flag);
}
