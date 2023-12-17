/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlstnew_with_mat.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 12:25:28 by Helene            #+#    #+#             */
/*   Updated: 2023/12/17 04:05:31 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

t_vlist	*ft_vlstnew_with_mat(void *content, void foo(void *), t_type t,
		t_material mat)
{
	t_vlist	*new;

	new = ft_vlstnew(content, foo, t);
	new->material = mat;
	set_checkerboard_map(&new->material.textures.checkerboard, new->type,
		(t_color){0xffffff});
	return (new);
}
