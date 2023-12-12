/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prod_mat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Helene <Helene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 22:46:09 by srapin            #+#    #+#             */
/*   Updated: 2023/12/12 18:33:26 by Helene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/matrices.h"

t_matrix    *matrix_product(t_matrix *a, t_matrix *b)
{
    int i = 0;
    int j = 0;
    int k = 0;
    t_matrix    *new;
    
    if (a->columns != b->rows)
	{
		ft_printf("can t multiply these matrix\n");
        return (NULL); /* msg d'erreur si non multipliable ? */
	}
    new = new_void_matrix(a->rows, b->columns);
    
    i = 0;
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
    
/* c[i][k] = SUM(j = 1, j <= N)(a_ij * b_jk) */
}

t_matrix    *scalar_product(t_matrix *a, double s)
{
    int i;
    int j;
    t_matrix *new;

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