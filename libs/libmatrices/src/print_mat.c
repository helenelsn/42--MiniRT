/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_mat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:15:17 by srapin            #+#    #+#             */
/*   Updated: 2023/11/08 18:37:48 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/matrices.h"

void print_mat(t_matrix *m)
{
	printf("r = %d, c = %d\n", m->rows, m->columns);
	int i = 0;
	int j = 0;

	while (i < m->rows)
	{
		while (j < m->columns)
		{
			printf("%f ", m->matrix[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}