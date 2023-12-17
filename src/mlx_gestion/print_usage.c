/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_usage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 18:31:04 by srapin            #+#    #+#             */
/*   Updated: 2023/12/17 05:39:00 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

void	print_elem_selected(int mute, t_type t)
{
	(void)t;
	if (mute)
		return ;
	printf("%s\n", __func__);
}

void	print_usage(int mute)
{
	if (mute)
		return ;
	printf("%s\n", __func__);
}
