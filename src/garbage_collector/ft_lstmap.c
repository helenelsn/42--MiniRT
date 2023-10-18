/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_glstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 04:24:34 by srapin            #+#    #+#             */
/*   Updated: 2023/10/18 22:12:04 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

t_glist	*ft_glstmap(t_glist *lst, void *(*f)(void *), void (*del)(void *))
{
	t_glist	*start;
	t_glist	*last;

	if (!lst)
		return (NULL);
	start = ft_glstnew(f(lst->content));
	if (!start)
		return (NULL);
	lst = lst->next;
	last = start;
	while (lst)
	{
		last->next = ft_glstnew(f(lst->content));
		if (!last->next)
		{
			ft_glstclear(&start, del);
			return (NULL);
		}
		last = last->next;
		lst = lst->next;
	}
	return (start);
}
