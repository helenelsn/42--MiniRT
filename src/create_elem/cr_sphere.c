/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_sphere.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 01:20:17 by srapin            #+#    #+#             */
/*   Updated: 2023/12/17 00:22:01 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

t_sphere	*create_sphere(char **tab, t_parsing_data *data)
{
	t_sphere *elem;
	t_material mat;
	int size_tab;
	ft_bzero(&mat, sizeof(t_material));

	size_tab = null_term_tab_len((void **)tab);
	if (size_tab < SP_PL_ARG_SIZE || size_tab > SP_PL_ARG_SIZE + BONUS_SIZE)
		return (NULL);
	elem = ft_calloc(1, sizeof(t_sphere));
	if (!elem)
		return (NULL);
	elem->radius = atof(tab[2]) / 2;
	init_mat(&mat);
	if (!get_rgb(tab[3], &mat.color) || !ft_strisfloat(tab[2])
		|| elem->radius < 0 || !get_point(tab[1], &elem->p)
		|| !set_bonus_options(&mat, tab + SP_PL_ARG_SIZE))
	{
		free(elem);
		return (NULL);
	}
    ft_vlstadd_back(&data->objects, ft_vlstnew_with_mat(elem, free,
                sphere, mat));
    return (elem);
}