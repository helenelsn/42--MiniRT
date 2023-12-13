/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_base.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eva <eva@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 00:03:13 by srapin            #+#    #+#             */
/*   Updated: 2023/12/13 01:05:21 by eva              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

t_vec change_base_of_vec(t_vec v, t_vec trans, t_matrix *rot)
{
	t_vec ret;
	t_matrix *tmp;
	t_matrix *tmp2;

	tmp = new_matrix_from_var_args(3, 1, v.x,v.y,v.z);	
	// printf("--------------------------------------------\n");
	
	// print_mat(tmp);
	tmp2 = matrix_product(rot, tmp);
	// print_mat(tmp2);
	// del_mat(tmp);
	ret.x = tmp2->matrix[0][0];
	ret.y = tmp2->matrix[1][0];
	ret.z = tmp2->matrix[2][0];
	ret = vect_addition(ret, trans);  // ret = vect_addition(v, trans); 
	return ret;
	
}

// t_point change_base_of_point(t_point v, t_vec trans, t_matrix *rot)
// {
// 	t_vec ret;
// 	t_point true_ret;
// 	t_matrix *tmp;
// 	t_matrix *tmp2;

// 	tmp = new_matrix_from_var_args(3, 1, v.x,v.y,v.z);	
// 	// printf("--------------------------------------------\n");
	
// 	print_mat(tmp);
// 	tmp2 = matrix_product(rot, tmp);
// 	print_mat(tmp2);
// 	del_mat(tmp);
// 	ret.x = tmp2->matrix[0][0];
// 	ret.y = tmp2->matrix[1][0];
// 	ret.z = tmp2->matrix[2][0];
// 	ret = vect_addition(v, trans);
// 	return ret;
	
// }