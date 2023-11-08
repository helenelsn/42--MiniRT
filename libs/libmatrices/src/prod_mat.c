/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prod_mat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 22:46:09 by srapin            #+#    #+#             */
/*   Updated: 2023/11/08 22:50:55 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/matrices.h"


// t_matrix  *matrix_product(t_matrix a, t_matrix b)
// {
//     int i;
//     int j;
//     int k;
//     t_matrix    *new;
    
//     if (a.columns != b.rows)
//         return (NULL); /* msg d'erreur si non multipliable ? */
//     // new = ft_calloc(sizeof(t_matrix), 1);
//     // if (!new)
//     //     return (NULL);
//     // new = new_void_matrix();
    
//     i = 0;
//     while (i < a.rows)
//     {
//         k = 0;
//         while (k < b.columns)
//         {
//             j = 0;
//             while (j < a.columns) /* ou b.rows */
//             {
//                 new->matrix[i][k] += a.matrix[i][j] * b.matrix[j][k];
//                 j++;
//             }
//             k++;
//         }
//         i++;
//     }
//     return (new);
    
// /* c[i][k] = SUM(j = 1, j <= N)(a_ij * b_jk) */
// }

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