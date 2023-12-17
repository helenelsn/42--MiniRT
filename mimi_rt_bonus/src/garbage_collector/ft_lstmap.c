/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 04:24:34 by srapin            #+#    #+#             */
/*   Updated: 2023/12/17 22:51:23 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt_bonus.h"

t_vlist	*ft_vlstmap(t_vlist *lst, void *(*f)(void *), void (*del)(void *))
{
	t_vlist	*start;
	t_vlist	*last;

	if (!lst)
		return (NULL);
	start = ft_vlstnew(f(lst->content));
	if (!start)
		return (NULL);
	lst = lst->next;
	last = start;
	while (lst)
	{
		last->next = ft_vlstnew(f(lst->content));
		if (!last->next)
		{
			ft_vlstclear(&start, del);
			return (NULL);
		}
		last = last->next;
		lst = lst->next;
	}
	return (start);
}
