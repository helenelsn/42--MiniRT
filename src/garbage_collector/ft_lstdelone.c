/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_glstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 04:23:58 by srapin            #+#    #+#             */
/*   Updated: 2023/10/18 22:15:54 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

void	ft_glstdelone(t_glist *lst)
{
	if (lst)
	{
		if (lst->content)
			lst->free_foo(lst->content);
		free(lst);
	}
}
