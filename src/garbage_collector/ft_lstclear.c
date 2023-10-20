/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 04:24:11 by srapin            #+#    #+#             */
/*   Updated: 2023/10/18 22:12:04 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

void	ft_vlstclear(t_vlist **lst)
{
	t_vlist	*tmp;

	while (lst && *lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		ft_vlstdelone(tmp);
	}
	lst = NULL;
}
