/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_inter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Helene <Helene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:20:33 by srapin            #+#    #+#             */
/*   Updated: 2023/11/22 00:26:21 by Helene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

t_vlist    *get_inter(t_vlist *elem, t_droite d) //clairement pas void mais j'ai pas d'idée
{
    if (elem->type == sphere)
        get_inter_for_sphere((t_sphere *) elem->content, d);
    else if (elem->type == plan)
        get_inter_for_plan((t_plan *) elem->content, d);
    
    return (NULL); // pour que ça compile
}