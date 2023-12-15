/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 20:05:35 by srapin            #+#    #+#             */
/*   Updated: 2023/12/15 20:23:47 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"


t_normal_map *get_map_char(t_nmaps t)
{
    
}

t_nmaps get_type_char(char *name)
{
    if (ft_strisequal(name, "cliff"))
        return cliff;
    if (ft_strisequal(name, "sand"))
        return sand;
    if (ft_strisequal(name, "terrain"))
        return terrain;
    if (ft_strisequal(name, "tree"))
        return tree;
    if (ft_strisequal(name, "wood"))
        return wood;
}