/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intervals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 16:00:55 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/17 04:10:20 by srapin           ###   ########.fr       */
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
