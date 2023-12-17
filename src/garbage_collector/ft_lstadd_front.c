/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 04:23:07 by srapin            #+#    #+#             */
/*   Updated: 2023/12/17 04:04:28 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

void	ft_vlstadd_front(t_vlist **lst, t_vlist *new)
{
	new->next = *lst;
	*lst = new;
}
