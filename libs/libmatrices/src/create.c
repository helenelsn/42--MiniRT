/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:44:06 by srapin            #+#    #+#             */
/*   Updated: 2023/11/08 23:44:23 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/matrices.h"

t_matrix  *new_matrix_from_var_args(int r, int c, ...)
{
    t_matrix *m;
    va_list ap;
    int i = 0;
    int j;
    
    m = new_void_matrix(r, c);
    va_start(ap, c);
    while (i < m->rows)
    {
        j = 0;
        while (j < m->columns)
        {
            m->matrix[i][j] = va_arg(ap, double);
            j++;
        }
        i++;
    }
    return m;
}

t_matrix  *new_matrix_from_tab(int r, int c, double **tab)
{
    t_matrix *m;
    
    m = ft_calloc(1, sizeof(t_matrix));
    m->rows = r;
    m->columns = c;
    m->matrix = tab;
    return m;
}


t_matrix  *new_void_matrix(int r, int c)
{
    t_matrix *m;
    int i = 0;
    
    m = ft_calloc(1, sizeof(t_matrix));
    m->rows = r;
    m->columns = c;
    m->matrix = ft_calloc(m->rows, sizeof(double *));
    while (i < m->rows)
    {
        m->matrix[i] = ft_calloc(m->columns, sizeof(double));
        i++;
    }
    return m;
}

t_matrix  *copy_matrix(t_matrix *m)
{
    t_matrix *new;
    int i =0;
    int j;

    new = new_void_matrix(m->rows, m->columns);
    while (i < m->rows)
    {
        j = 0;
        while (j < m->columns)
        {
            new->matrix[i][j] = m->matrix[i][j];
            j++;
        }
        i++;
    }
    return new;
}