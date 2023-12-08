/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cofactore_matrix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 20:46:32 by srapin            #+#    #+#             */
/*   Updated: 2023/12/06 22:12:08 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/matrices.h"

t_matrix *get_cofactor_matrix(t_matrix *m)
{
	int i = 0;
	int j = 0;
	double det;
	t_matrix *new = new_void_matrix(m->rows, m->columns);
	
	t_matrix *tmp;
	// printf(" \n\n\n\n\n\n\n");
	// printf("matrix = \n");
	// print_mat(m);
	// printf(" \n\n\n\n\n\n\n");
	while(i < m->rows)
	{
		j = 0;
		while(j < m->columns)
		{
			tmp = get_sub_matrix(m, i, j);
			det = get_mat_det(tmp);
			if ((i+j)%2)
				det *= -1;
			new->matrix[i][j] = det;
			del_mat(tmp);
			j++;
		}
		i++;
	}
	// printf("cofactor = \n");
	// print_mat(new);
	return new;
}