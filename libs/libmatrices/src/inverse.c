/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 00:29:05 by srapin            #+#    #+#             */
/*   Updated: 2023/12/14 16:01:26 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/matrices.h"

t_matrix *get_inverse(t_matrix *m)
{
	t_matrix *t;
	t_matrix *inv;
	double d;

	d = get_mat_det(m);
	// print_mat(m);
	if (!d)
	{
		// printf("det is null can not inv matrix\n");
		return NULL;
	}
	t=transpose(m);
	inv = get_cofactor_matrix(t);
	scalar_product(inv, 1/d);
	// print_mat(inv);
	return inv;
}