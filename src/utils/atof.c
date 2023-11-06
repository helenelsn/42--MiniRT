/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atof.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 00:10:01 by srapin            #+#    #+#             */
/*   Updated: 2023/11/05 22:47:11 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

double	ft_atof(char *nptr)
{
	int		i;
	int		neg;
	double	dec;
	int		number;

	number = ft_atoi(nptr);
	if (ft_strisint(nptr))
		return (number);
	i = ft_strlen(nptr) - 1;
	dec = 0.0;
	neg = 1;
	if (!nptr)
		return (0.0);
	if (number < 0)
		neg = -1;
	while (i >= 0 && ft_isdigit(nptr[i]))
	{
		dec = dec / 10 + (nptr[i] - 48);
		i--;
	}
	return (number + neg * dec);
}
