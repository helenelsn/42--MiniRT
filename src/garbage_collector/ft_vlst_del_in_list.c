/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlst_del_in_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:17:39 by hlesny            #+#    #+#             */
/*   Updated: 2023/11/09 23:17:03 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

// void	ft_vlst_del_in_list(t_vlist **lst, t_vlist *todel)
// {
// 	// t_vlist	*tmp;
// 	t_vlist *node;
// 	t_vlist *prev = NULL;
	
// 	node = *lst;
	
// 	if (!todel)
//     	return ;
// 	while (lst && node && node != todel)
// 	{
// 		prev = node;
//     	node = node->next;
// 	}
//     if (lst && node)
// 	{
// 		if (node->next)
// 		{
// 			prev->next = node->next;
// 			node->next = NULL;
// 		}
// 		else if (prev)
// 			prev->next = NULL;
// 		else
// 			*lst = NULL;
// 			// (*lst)->next = NULL;
		
// 		// ft_vlstdelone(*lst);
// 	}
// }