/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 20:52:41 by Helene            #+#    #+#             */
/*   Updated: 2023/12/17 23:00:20 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRICES_H
# define MATRICES_H

# include "../../../mimi_rt/inc/struct.h"
#include <stdarg.h>
#include "../../libft/ft_printf.h"

typedef struct s_cofactor_calc
{
	bool		row;
	int			zeros_count;
	int			index;
}				t_cofactor_info;

t_matrix		*get_cofactor_matrix(t_matrix *m);

//create
t_matrix		*new_void_matrix(int r, int c);
t_matrix		*new_matrix_from_tab(int r, int c, double **tab);
t_matrix		*copy_matrix(t_matrix *m);
t_matrix		*new_matrix_from_var_args(int r, int c, ...);
t_matrix		*transpose(t_matrix *m);
bool			matrix_are_equals(t_matrix *a, t_matrix *b);
t_matrix		*get_sub_matrix(t_matrix *m, int r, int c);
t_matrix		*matrix_product(t_matrix *a, t_matrix *b);
t_matrix		*scalar_product(t_matrix *a, double s);
t_matrix		*get_inverse(t_matrix *a);
t_matrix		*new_3x3_matrix_from_vec(t_vec v0, t_vec v1, t_vec v2,
					bool lign);
void			del_mat(void *v);
void			print_mat(t_matrix *m);
t_cofactor_info	scan_mat(t_matrix *m);
double			get_mat_det(t_matrix *m);
void			set_2_int_to_null(int *a, int *b);
void			incr_2_int(int *a, int *b);
void			update_res(double *res, t_matrix *m, int i, int j);
int				get_det_sign(int row, int col);
#endif