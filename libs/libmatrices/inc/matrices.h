/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 20:52:41 by Helene            #+#    #+#             */
/*   Updated: 2023/11/09 18:17:10 by srapin           ###   ########.fr       */
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
t_matrix  *copy_matrix(t_matrix *m);
t_matrix  *new_matrix_from_var_args(int r, int c, ...);

/* retourner un pointeur ? */
// t_matrix    new_matrix(double *u1, double *u2, double *u3);
t_matrix    *transpose(t_matrix *m);
bool    matrix_are_equals(t_matrix *a, t_matrix *b);
t_matrix *get_sub_matrix(t_matrix *m, int r, int c);
t_matrix    *matrix_product(t_matrix *a, t_matrix *b);
t_matrix    *scalar_product(t_matrix *a, double s);
t_matrix    *inverse(t_matrix a);
// bool        are_equals(t_matrix a, t_matrix b);

void	del_mat(void *v);

void print_mat(t_matrix *m);

// int		get_best_col(t_matrix *m);
// int		get_best_row(t_matrix *m);

t_cofactor_info scan_mat(t_matrix *m);
double get_mat_det(t_matrix *m);
#endif