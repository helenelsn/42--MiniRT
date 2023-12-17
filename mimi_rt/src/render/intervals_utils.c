/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intervals_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:09:10 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/17 01:06:07 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"
#include "../../inc/struct.h"

t_interval	get_interval(double min, double max)
{
	t_interval	t;

	t.min = min;
	t.max = max;
	return (t);
}
