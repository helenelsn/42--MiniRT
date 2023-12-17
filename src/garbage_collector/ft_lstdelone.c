/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 04:23:58 by srapin            #+#    #+#             */
/*   Updated: 2023/12/17 04:03:42 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

void	ft_vlstdelone(t_vlist *lst)
{
	if (lst)
	{
		if (lst->content)
			lst->free_foo(lst->content);
		free(lst);
		lst = NULL;
	}
}
