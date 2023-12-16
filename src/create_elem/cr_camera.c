/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_camera.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 00:53:38 by srapin            #+#    #+#             */
/*   Updated: 2023/12/16 23:43:08 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

t_camera	*create_camera(char **tab, t_parsing_data *data)
{
	t_camera	*elem;

	if (null_term_tab_len((void **)tab) != 4 || data->cam)
		return (NULL);
	elem = ft_calloc(1, sizeof(t_camera));
	if (!elem)
		return (NULL);
	elem->fov = get_fov(tab[3]);
	if (elem->fov < 0 || !get_point(tab[1], &elem->p)
		|| !get_vec_from_str(tab[2], &elem->direction))
	{
		free(elem);
		return (NULL);
	}
	data->cam = elem;
	return (elem);
}
