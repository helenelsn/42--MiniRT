/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 02:09:59 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/17 22:51:23 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/struct_bonus.h"
#include "../../../../inc/mini_rt_bonus.h"

bool	ft_is_equalsf(const float a, const float b, const float tolerance)
{
	return ((a + tolerance >= b) && (a - tolerance <= b));
}

float	fmodf_positive(float dividend, float divisor)
{
	float	result;

	result = fmodf(dividend, divisor);
	if (result < 0)
		result = divisor + result;
	return (result);
}
