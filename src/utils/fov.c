/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 00:46:56 by srapin            #+#    #+#             */
/*   Updated: 2023/10/19 00:48:03 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

int get_fov(char *str)
{
    if (!str || !ft_strisint(str))
        return (-1);
    int nb;
    nb = atoi(str);
    if (0 > nb || 180 < nb)
        return(-1);
    return (nb);
}