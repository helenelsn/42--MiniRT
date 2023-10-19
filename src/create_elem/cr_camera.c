/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_camera.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 00:53:38 by srapin            #+#    #+#             */
/*   Updated: 2023/10/19 01:01:34 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

t_camera *create_camera(char **tab, t_glist **garbage)
{
    t_camera *elem;

    if (null_term_tab_len((void **) tab) != 4)
        return NULL;
    elem = ft_calloc(1, sizeof(t_camera));
    if (!elem)
        return NULL;
    elem->fov = get_fov(tab[3]);
    if (elem->fov < 0 || !get_point(tab[1], &elem->p) || !get_vec(tab[2], &elem->vec))
    {
        free(elem);
        return NULL;
    }
    ft_glstadd_back(garbage, ft_glstnew(elem, free));
    return elem;
}