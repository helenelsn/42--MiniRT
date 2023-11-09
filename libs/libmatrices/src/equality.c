/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equality.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 00:36:01 by srapin            #+#    #+#             */
/*   Updated: 2023/11/09 00:39:33 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/matrices.h"

bool    matrix_are_equals(t_matrix *a, t_matrix *b)
{
    int i;
    int j;
    
    if (a->columns != b->columns || a->rows != b->rows)
        return (false);
    i = 0;
    while (i < a->rows)
    {
        j = 0;
        while (j < a->columns)
        {
            if (a->matrix[i][j] != b->matrix[i][j])
                return (false);
            j++;
        }
        i++;
    }
    return (true);
}