/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_camera.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 00:53:38 by srapin            #+#    #+#             */
/*   Updated: 2023/12/12 18:47:03 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

t_camera *create_camera(char **tab, t_vlist **garbage, t_parsing_data *data)
{
    t_camera *elem;
    
    
    if (null_term_tab_len((void **) tab) != 4 || data->cam)
        return NULL;
    elem = ft_calloc(1, sizeof(t_camera));
    if (!elem)
        return NULL;
    elem->fov = get_fov(tab[3]);
    if (elem->fov < 0 || !get_point(tab[1], &elem->p) || !get_vec_from_str(tab[2], &elem->direction))
    {
        free(elem);
        return NULL;
    }
    ft_vlstadd_back(garbage, ft_vlstnew(elem, free, camera));
    data->cam = elem;
    return elem;
}