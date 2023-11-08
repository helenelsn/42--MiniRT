/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 20:52:41 by Helene            #+#    #+#             */
/*   Updated: 2023/11/08 18:19:17 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once
#ifndef MATRICES_H
# define MATRICES_H

#include "../../../inc/mini_rt.h"
#include <stdbool.h>

typedef struct  s_matrix
{
    int     rows;
    int     columns;
    double  **matrix;
}               t_matrix;

typedef struct  s_cofactor_calc
{
    bool    row; /* true if is a row, false otherwise */
    int     zeros_count;
    int     index;
}               t_cofactor_info;


//create
t_matrix  *new_void_matrix(int r, int c);
t_matrix  *new_matrix_from_tab(int r, int c, double **tab);

/* retourner un pointeur ? */
// t_matrix    new_matrix(double *u1, double *u2, double *u3);
t_matrix    *matrix_product(t_matrix a, t_matrix b);
t_matrix    *scalar_product(t_matrix a, double s);
t_matrix    *inverse(t_matrix a);
// bool        are_equals(t_matrix a, t_matrix b);


void print_mat(t_matrix *m);

#endif