/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_cone.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:59:16 by srapin            #+#    #+#             */
/*   Updated: 2023/12/17 22:51:23 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt_bonus.h"

void	set_cone_dep(t_cone *elem)
{
	t_ray	tmp;

	tmp.origin = elem->p;
	tmp.direction = elem->vec;
	elem->top = get_ray_point(tmp, elem->height);
	elem->cover_plane = (t_plan){elem->p, elem->vec, 0, 0, 0, 0};
	set_eq(&elem->cover_plane);
}

t_cone	*create_cone(char **tab, t_parsing_data *data)
{
	t_material	mat;
	t_cone		*elem;
	int			size_tab;

	size_tab = null_term_tab_len((void **)tab);
	if (size_tab < CO_CY_ARG_SIZE || size_tab > CO_CY_ARG_SIZE + BONUS_SIZE)
		return (NULL);
	elem = ft_calloc(1, sizeof(t_cone));
	if (!elem)
		return (NULL);
	init_mat(&mat);
	elem->radius = atof(tab[3]) * (1 - 2 * !ft_strisfloat(tab[3])) / 2;
	elem->height = atof(tab[4]) * (1 - 2 * !ft_strisfloat(tab[4]));
	if (!get_rgb(tab[5], &mat.color) || elem->radius < 0 || elem->height < 0
		|| !get_point(tab[1], &elem->p) || !get_vec_from_str(tab[2], &elem->vec)
		|| !set_bonus_options(&mat, tab + CO_CY_ARG_SIZE))
	{
		free(elem);
		return (NULL);
	}
	normalise(&elem->vec);
	set_cone_dep(elem);
	ft_vlstadd_back(&data->objects, ft_vlstnew_with_mat(elem, free, cone, mat));
	return (elem);
}
