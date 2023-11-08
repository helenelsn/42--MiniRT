/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 21:01:11 by Helene            #+#    #+#             */
/*   Updated: 2023/11/08 22:45:40 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/matrices.h"


// t_matrix  new_matrix(double *u1, double *u2, double *u3)
// {

// }



/* a * b */


t_matrix    transpose(t_matrix a)
{
    int         i;
    int         j;
    t_matrix    b;

    // b = malloc(sizeof(t_matrix));
    // if (!b)
    //     return (NULL);
    i = 0;
    b.columns = a.rows;
    b.rows = a.columns;
    while (i < a.rows)
    {
        j = 0;
        while (j < a.columns)
        {
            b.matrix[j][i] = a.matrix[i][j];
            j++;
        }
        i++;
    }
    return (b);
}

t_cofactor_info  scan_rows(t_matrix a)
{
    int i;
    int j;
    int curr_zeros_count;
    t_cofactor_info info;

    i = 0;
    curr_zeros_count = 0;
    info.zeros_count = 0;
    info.row = true;
    while (i < a.rows)
    {
        j = 0;
        curr_zeros_count = 0;
        while (j < a.columns)
        {
            if (!a.matrix[i][j])
                curr_zeros_count++;
            j++;
        }
        if (curr_zeros_count > info.zeros_count)
        {
            info.zeros_count = curr_zeros_count;
            info.index = i;
        }
        i++;
    }
    return (info);
}

t_cofactor_info  scan_columns(t_matrix a)
{
    int i;
    int j;
    int curr_zeros_count;
    t_cofactor_info info;

    j = 0;
    curr_zeros_count = 0;
    info.zeros_count = 0;
    info.row = false;
    while (j < a.columns)
    {
        i = 0;
        curr_zeros_count = 0;
        while (i < a.rows)
        {
            if (!a.matrix[i][j])
                curr_zeros_count++;
            i++;
        }
        if (curr_zeros_count > info.zeros_count)
        {
            info.zeros_count = curr_zeros_count;
            info.index = j;
        }
        j++;
    }
    return (info);
}

t_cofactor_info get_efficient_index(t_matrix a) 
{
    t_cofactor_info cr;
    t_cofactor_info cc;

    cr = scan_rows(a);
    cc = scan_columns(a);
    if (cr.zeros_count > cc.zeros_count)
        return (cr);
    return (cc);
}

// t_matrix    compute_cofactor_m(t_matrix a)
// {
    
// }

// double  compute_determinant(t_matrix a)
// {
    
// }

t_matrix  *inverse(t_matrix a)
{
    double      det;
    t_matrix    cofactor_mat;
    if (a.rows != a.columns)
        return (NULL);
    
    det = compute_determinant(a);
    if (!det)
        return (NULL);
    // cofactor_mat = compute_cofactor_m(a);
    return NULL;
    return (scalar_product(transpose(cofactor_mat), 1/det));
}

bool    are_equals(t_matrix a, t_matrix b)
{
    int i;
    int j;
    
    if (a.columns != b.columns || a.rows != b.rows)
        return (false);
    i = 0;
    while (i < a.rows)
    {
        j = 0;
        while (j < a.columns)
        {
            if (a.matrix[i][j] != b.matrix[i][j])
                return (false);
            j++;
        }
        i++;
    }
    return (true);
}
