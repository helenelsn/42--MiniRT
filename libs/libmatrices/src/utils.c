/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 05:25:17 by srapin            #+#    #+#             */
/*   Updated: 2023/12/17 05:28:08 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/matrices.h"

int	get_det_sign(int row, int col)
{
	if ((row + col) % 2)
		return (-1);
	return (1);
}

void	update_res(double *res, t_matrix *m, int i, int j)
{
	t_matrix	*tmp;

	tmp = get_sub_matrix(m, i, j);
	*res += get_det_sign(i, j) * m->matrix[i][j] * get_mat_det(tmp);
	del_mat(tmp);
}

void	incr_2_int(int *a, int *b)
{
	*a = *a + 1;
	*b = *b + 1;
}

void	set_2_int_to_null(int *a, int *b)
{
	*a = 0;
	*b = 0;
}
