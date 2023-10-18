/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_glstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 04:23:40 by srapin            #+#    #+#             */
/*   Updated: 2023/10/18 22:12:04 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

void	ft_glstadd_back(t_glist **lst, t_glist *new)
{
	t_glist	*last;

	if (lst)
		last = ft_glstlast(*lst);
	else
		last = NULL;
	if (last)
		last->next = new;
	else
		*lst = new;
}
