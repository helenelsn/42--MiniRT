/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 00:46:56 by srapin            #+#    #+#             */
/*   Updated: 2023/12/17 02:42:16 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

int	get_fov(char *str)
{
	int	nb;

	if (!str || !ft_strisint(str))
		return (-1);
	nb = atoi(str);
	if (0 > nb || 180 < nb)
		return (-1);
	return (nb);
}
