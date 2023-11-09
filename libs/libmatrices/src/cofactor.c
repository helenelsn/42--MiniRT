/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cofactor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 00:40:26 by srapin            #+#    #+#             */
/*   Updated: 2023/11/09 01:47:00 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/matrices.h"


t_matrix *get_sub_matrix(t_matrix *m, int r, int c)
{
	t_matrix *res;

	res = new_void_matrix(m->rows -1, m->columns - 1);
	
	int i = 0;
	int j = 0;
	int k = 0;
	int l = 0;

	while(k < res->rows)
	{
		j = 0;
		l = 0;
		if (i == r)
			i++;
		while (l < res->columns)
		{
			if (j == c)
				j++;
			// printf("%f\n", m->matrix[i][j]);
			if (i < m->rows && j < m->columns)
				res->matrix[k][l] = m->matrix[i][j];
			j++;
			l++;
		}
		i++;
		k++;
	}
	return res;
}

double get_det_2x2_or_less_matrix(t_matrix m)
{
	if (m->rows != m->columns || m->rows > 2)
	{
		printf("PROBLEME\n");
		return 0;
	}
	if (m->rows == 1)
		return (m->matrix[0][0]);
	if (m->rows == 2)
		return (m->matrix[0][0] * m->matrix[1][1] - m->matrix[0][1] * m->matrix[1][0]);
}

t_matrix *get_minor_matrix(t_matrix *m)
{
	t_matrix *res;
	t_matrix *tmp;
	int i = 0;
	int j = 0;

	res = new_void_matrix(m->rows, m->columns);
	
	while(i < m->rows)
	{
		j =0;
		while(j < m->columns)
		{
			tmp = get_sub_matrix(m, i, j);
			m->matrix
			del_mat(tmp);
			j++;
		}
		i++;
	}
}