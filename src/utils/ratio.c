/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ratio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 00:16:45 by srapin            #+#    #+#             */
/*   Updated: 2023/12/17 02:50:28 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

double	get_ratio(char *str)
{
	double	nb;

	if (!str || !ft_strisfloat(str))
		return (-1);
	nb = atof(str);
	if (0 > nb || 1 < nb)
		return (-1);
	return (nb);
}
