/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 04:11:10 by srapin            #+#    #+#             */
/*   Updated: 2023/12/17 22:51:23 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt_bonus.h"

t_vlist	*ft_vlstnew(void *content, void foo(void *), t_type t)
{
	t_vlist	*new_lst;

	new_lst = malloc(sizeof(t_vlist));
	if (!new_lst)
		return (NULL);
	new_lst->next = NULL;
	new_lst->content = content;
	new_lst->free_foo = foo;
	new_lst->type = t;
	return (new_lst);
}
