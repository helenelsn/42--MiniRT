/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_checkers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 21:28:35 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/17 03:32:50 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

bool	set_checkers(char *str, bool *to_mod)
{
	int	n;

	*to_mod = false;
	if (!str)
		return (true);
	if (!ft_strisint(str))
		return (false);
	n = atof(str);
	if (n && n != 1)
		return (false);
	*to_mod = (n == 1);
	return (true);
}
