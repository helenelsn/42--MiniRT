/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 04:23:40 by srapin            #+#    #+#             */
/*   Updated: 2023/10/18 22:12:04 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

void	ft_vlstadd_back(t_vlist **lst, t_vlist *new)
{
	t_vlist	*last;

	if (lst)
		last = ft_vlstlast(*lst);
	else
		last = NULL;
	if (last)
		last->next = new;
	else
		*lst = new;
}
