/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_cylindre.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 01:29:43 by srapin            #+#    #+#             */
/*   Updated: 2023/12/17 00:22:14 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

void	set_cylindre_dep(t_cylindre *elem)
{
	t_ray	tmp;

	tmp.origin = elem->p;
	tmp.direction = elem->vec;
	elem->cover_planes[0] = (t_plan){get_ray_point(tmp, elem->height / 2),
										elem->vec,
										0,
										0,
										0,
										0};
	elem->cover_planes[1] = (t_plan){get_ray_point(tmp, -elem->height / 2),
										elem->vec,
										0,
										0,
										0,
										0};
	set_eq(&elem->cover_planes[0]);
	set_eq(&elem->cover_planes[1]);
}

t_cylindre	*create_cylindre(char **tab, t_parsing_data *data)
{
	t_cylindre *elem;

	t_material mat;
	init_mat(&mat);
	int size_tab = null_term_tab_len((void **)tab);
	if (size_tab < CO_CY_ARG_SIZE || size_tab > CO_CY_ARG_SIZE + BONUS_SIZE)
		return (NULL);
	elem = ft_calloc(1, sizeof(t_cylindre));
	if (!elem)
		return (NULL);
	elem->radius = atof(tab[3]) * (1 - 2 * !ft_strisfloat(tab[3])) / 2;
	//j'trouve c est stylé
	elem->height = atof(tab[4]) * (1 - 2 * !ft_strisfloat(tab[4]));
	//j'trouve c est stylé
	if (!get_rgb(tab[5], &mat.color) || elem->radius < 0 || elem->height < 0
		|| !get_point(tab[1], &elem->p) || !get_vec_from_str(tab[2], &elem->vec)
		|| !set_bonus_options(&mat, tab + CO_CY_ARG_SIZE))
	{
		free(elem);
		return (NULL);
	}
	normalise(&elem->vec);
	set_cylindre_dep(elem);
	ft_vlstadd_back(&data->objects, ft_vlstnew_with_mat(elem, free, cylindre,
				mat));
	return (elem);
}
