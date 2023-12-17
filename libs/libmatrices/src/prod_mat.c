/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prod_mat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 22:46:09 by srapin            #+#    #+#             */
/*   Updated: 2023/12/17 04:31:22 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/matrices.h"

t_matrix	*matrix_product(t_matrix *a, t_matrix *b)
{
	int			i;
	int			j;
	int			k;
	t_matrix	*new;

	i = 0;
	k = 0;
	new = new_void_matrix(a->rows, b->columns);
	while (i < a->rows)
	{
		j = 0;
		while (j < b->columns)
		{
			new->matrix[i][j] = 0;
			k = 0;
			while (k < a->columns)
			{
				new->matrix[i][j] += a->matrix[i][k] * b->matrix[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
	return (new);
}

t_matrix	*scalar_product(t_matrix *a, double s)
{
	t_matrix	*new;
	int			i;
	int			j;

	new = copy_matrix(a);
	i = 0;
	while (i < new->rows)
	{
		j = 0;
		while (j < new->columns)
		{
			new->matrix[i][j] *= s;
			j++;
		}
		i++;
	}
	return (new);
}
