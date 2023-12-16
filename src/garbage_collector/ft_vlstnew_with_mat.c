/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlstnew_with_mat.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Helene <Helene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 12:25:28 by Helene            #+#    #+#             */
/*   Updated: 2023/12/16 12:27:59 by Helene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

t_vlist *ft_vlstnew_with_mat(void * content, void foo(void *), t_type t,
    t_material mat)
{
    t_vlist *new;

    new = ft_vlstnew(content, foo, t);
    new->material = mat;

    //todel
    new->material.textures.checkered = false;
    // new->material.textures.bump_mapping = true; //ln
    
    set_checkerboard_map(&new->material.textures.checkerboard, new->type, (t_color){0xffffff});
    
    // set_color_in_mat(content, &mat, t);
    // printf("%d", mat.color);
    return (new);
}