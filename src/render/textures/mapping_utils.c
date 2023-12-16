/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 02:09:59 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/16 02:17:56 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/struct.h"
#include "../../../inc/mini_rt.h"

bool	ft_is_equalsf(const float a, const float b, const float tolerance)
{
	return ((a + tolerance >= b) && (a - tolerance <= b));
}

double  rad_to_deg(double radians)
{
    return (radians * 180.0 / M_PI);
}

float	fmodf_positive(float dividend, float divisor)
{
	float	result;

	result = fmodf(dividend, divisor);
	if (result < 0)
		result = divisor + result;
	return (result);
}

// t_vec       vec_mat_product(t_vec v, t_matrix *m)
// {
//     t_vec   result;
//     ft_bzero(&result, sizeof(t_vec));
    
//     t_matrix *a = new_matrix_from_var_args(3, 1, v.x, v.y, v.z);
    
//     if (m->columns != 3)
//         return ((t_vec){0, 0, 0, 0});
    
//     for (int i = 0; i < 3; i++)
//     {
//         result.x += m->matrix[0][i] * a->matrix[i][0];
//         result.y += m->matrix[1][i] * a->matrix[i][0];
//         result.z += m->matrix[2][i] * a->matrix[i][0];
//     }

//     del_mat(a);
//     return (result);
// }