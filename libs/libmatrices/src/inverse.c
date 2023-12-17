/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 00:29:05 by srapin            #+#    #+#             */
/*   Updated: 2023/12/17 04:28:06 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/matrices.h"

t_matrix	*get_inverse(t_matrix *m)
{
	t_matrix	*t;
	t_matrix	*inv;
	double		d;

	d = get_mat_det(m);
	if (!d)
		return (NULL);
	t = transpose(m);
	inv = get_cofactor_matrix(t);
	scalar_product(inv, 1 / d);
	return (inv);
}
