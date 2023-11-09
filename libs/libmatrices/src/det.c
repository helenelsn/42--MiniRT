/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cofactor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 00:40:26 by srapin            #+#    #+#             */
/*   Updated: 2023/11/09 19:29:01 by srapin           ###   ########.fr       */
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

static double get_det_2x2_or_less_matrix(t_matrix *m)
{
	if (m->rows == 1)
		return (m->matrix[0][0]);
	if (m->rows == 2)
		return (m->matrix[0][0] * m->matrix[1][1] - m->matrix[0][1] * m->matrix[1][0]);
	printf("ERROR\n");
	return 0;
}



// t_matrix *get_minor_matrix(t_matrix *m)
// {
// 	t_matrix *res;
// 	t_matrix *tmp;
// 	int i = 0;
// 	int j = 0;

// 	res = new_void_matrix(m->rows, m->columns);
	
// 	while(i < m->rows)
// 	{
// 		j =0;
// 		while(j < m->columns)
// 		{
// 			tmp = get_sub_matrix(m, i, j);
// 			m->matrix[i][j] = get_mat_det(m);
// 			del_mat(tmp);
// 			j++;
// 		}
// 		i++;
// 	}
// }

int get_sign(int row, int col)
{
	if ((row+col) %2)
		return -1;
	return 1;
}

double get_mat_det(t_matrix *m)
{
	t_cofactor_info info;
	
	if (m->rows != m->columns)
	{
		printf("PROBLEME\n");
		return 0;
	}
	if (m->rows <= 2)
		return get_det_2x2_or_less_matrix(m);
	info = scan_mat(m);
	int i = -1;
	int res = 0;
	// printf("mat info : row = %d, index = %d\n", info.row, info.index);
	t_matrix *tmp;
	print_mat(m);
	info.row = 0;
	info.index = 0;
	while(++i < m->columns)
	{
		// if (info.row && m->matrix[info.index][i])
		if (info.row)
		{
			tmp = get_sub_matrix(m, info.index, i);
			// printf("%d %d\n", info.index, i);
			// print_mat(tmp);
			res += get_sign(info.index, i) * m->matrix[info.index][i] * get_mat_det(tmp);
			del_mat(tmp);
		}
		// if (!info.row && m->matrix[i][info.index])
		if (!info.row)
		{
			tmp = get_sub_matrix(m, i, info.index);
			// printf("sub_mat from r = %d c = %d\n",i,  info.index);
			// print_mat(tmp);
			res += get_sign(i, info.index) * m->matrix[i][info.index] * get_mat_det(tmp);
			del_mat(tmp);
		}
		// i++;
	}
	return res;
}