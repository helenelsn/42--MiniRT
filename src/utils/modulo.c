/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modulo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:25:26 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/17 02:46:27 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

int	ft_sign(double n)
{
	if (n < 0.0)
		return (-1);
	return (1);
}

double	f__mod_f(double a, int n)
{
	int		k;
	bool	neg;

	if (!n)
		return (0);
	k = 0;
	if (a < 0.0)
		neg = true;
	a = fabs(a);
	while (k * n < a)
		k++;
	if (neg)
		return (k * n - a);
	return (a - (k - 1) * n);
}
