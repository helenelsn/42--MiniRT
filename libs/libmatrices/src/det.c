/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   det.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 00:40:26 by srapin            #+#    #+#             */
/*   Updated: 2023/12/17 05:26:01 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/matrices.h"

t_matrix	*get_sub_matrix(t_matrix *m, int r, int c)
{
	t_matrix	*res;
	int			i;
	int			j;
	int			k;
	int			l;

	res = new_void_matrix(m->rows - 1, m->columns - 1);
	set_2_int_to_null(&k, &i);
	while (k < res->rows)
	{
		set_2_int_to_null(&l, &j);
		if (i == r)
			i++;
		while (l < res->columns)
		{
			if (j == c)
				j++;
			if (i < m->rows && j < m->columns)
				res->matrix[k][l] = m->matrix[i][j];
			incr_2_int(&j, &l);
		}
		incr_2_int(&i, &k);
	}
	return (res);
}

static double	get_det_2x2_or_less_matrix(t_matrix *m)
{
	if (m->rows == 1)
		return (m->matrix[0][0]);
	if (m->rows == 2)
		return (m->matrix[0][0] * m->matrix[1][1] - m->matrix[0][1]
			* m->matrix[1][0]);
	printf("ERROR\n");
	return (0);
}

double	get_mat_det(t_matrix *m)
{
	t_cofactor_info	info;
	int				i;
	double			res;

	if (m->rows != m->columns)
		return (0);
	if (m->rows <= 2)
		return (get_det_2x2_or_less_matrix(m));
	i = -1;
	res = 0;
	info = scan_mat(m);
	while (++i < m->columns)
	{
		if (info.row)
			update_res(&res, m, info.index, i);
		if (!info.row)
			update_res(&res, m, i, info.index);
	}
	return (res);
}
