/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlst_del_in_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:17:39 by hlesny            #+#    #+#             */
/*   Updated: 2023/11/09 20:32:44 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

void	ft_vlst_del_in_list(t_vlist **lst, t_vlist *todel)
{
	// t_vlist	*tmp;

	if (!todel)
    	return ;
	while (lst && *lst && *lst != todel)
    	*lst = (*lst)->next;
    if (lst && *lst)
	{
		if ((*lst)->next)
			(*lst)->next = (*lst)->next->next;
		else
			(*lst)->next = NULL;
		
		ft_vlstdelone(*lst);
	}
}