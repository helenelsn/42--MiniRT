/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   det.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 00:40:26 by srapin            #+#    #+#             */
/*   Updated: 2023/12/17 04:26:56 by srapin           ###   ########.fr       */
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
	k = 0;
	l = 0;
	while (k < res->rows)
	{
		j = 0;
		l = 0;
		if (i == r)
			i++;
		while (l < res->columns)
		{
			if (j == c)
				j++;
			if (i < m->rows && j < m->columns)
				res->matrix[k][l] = m->matrix[i][j];
			j++;
			l++;
		}
		i++;
		k++;
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

int	get_sign(int row, int col)
{
	if ((row + col) % 2)
		return (-1);
	return (1);
}

double	get_mat_det(t_matrix *m)
{
	t_cofactor_info	info;
	t_matrix		*tmp;
	int				i;
	int				res;

	if (m->rows != m->columns)
	{
		printf("PROBLEME\n");
		return (0);
	}
	if (m->rows <= 2)
		return (get_det_2x2_or_less_matrix(m));
	i = -1;
	res = 0;
	info = scan_mat(m);
	while (++i < m->columns)
	{
		if (info.row)
		{
			tmp = get_sub_matrix(m, info.index, i);
			res += get_sign(info.index, i) * m->matrix[info.index][i]
				* get_mat_det(tmp);
			del_mat(tmp);
		}
		if (!info.row)
		{
			tmp = get_sub_matrix(m, i, info.index);
			res += get_sign(i, info.index) * m->matrix[i][info.index]
				* get_mat_det(tmp);
			del_mat(tmp);
		}
	}
	return (res);
}
