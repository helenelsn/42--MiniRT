/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:33:38 by srapin            #+#    #+#             */
/*   Updated: 2023/11/09 18:07:18 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/matrices.h"


t_cofactor_info		get_best_row(t_matrix *m)
{
	t_cofactor_info ret;
	int curr_zero;
	int i = 0;
	int j;

	ret.row = true;
	ret.index = 0;
	ret.zeros_count = 0;
	while (i < m->rows)
	{
		j = 0;
		curr_zero = 0;
		while(j < m->columns)
		{
			if (m->matrix[i][j] == 0)
				curr_zero++;
			j++;
		}
		if (curr_zero > ret.zeros_count)
		{
			ret.zeros_count = curr_zero;
			ret.index = i;
		}
		i++;
	}
	return ret;	
}

t_cofactor_info		get_best_col(t_matrix *m)
{
	t_cofactor_info ret;
	int curr_zero;
	int i = 0;
	int j;

	ret.row = false;
	ret.index = 0;
	ret.zeros_count = 0;
	while (i < m->columns)
	{
		j = 0;
		curr_zero = 0;
		while(j < m->rows)
		{
			if (m->matrix[j][i] == 0)
				curr_zero++;
			j++;
		}
		if (curr_zero > ret.zeros_count)
		{
			ret.zeros_count = curr_zero;
			ret.index = i;
		}
		i++;
	}
	return ret;	
}



t_cofactor_info scan_mat(t_matrix *m)
{
	t_cofactor_info r = get_best_row(m);
	t_cofactor_info c = get_best_col(m);

	if (c.zeros_count > r.zeros_count)
		return c;
	return r;
}

// t_cofactor_info  scan_rows(t_matrix a)
// {
//     int i;
//     int j;
//     int curr_zeros_count;
//     t_cofactor_info info;

//     i = 0;
//     curr_zeros_count = 0;
//     info.zeros_count = 0;
//     info.row = true;
//     while (i < a.rows)
//     {
//         j = 0;
//         curr_zeros_count = 0;
//         while (j < a.columns)
//         {
//             if (!a.matrix[i][j])
//                 curr_zeros_count++;
//             j++;
//         }
//         if (curr_zeros_count > info.zeros_count)
//         {
//             info.zeros_count = curr_zeros_count;
//             info.index = i;
//         }
//         i++;
//     }
//     return (info);
// }

// t_cofactor_info  scan_columns(t_matrix a)
// {
//     int i;
//     int j;
//     int curr_zeros_count;
//     t_cofactor_info info;

//     j = 0;
//     curr_zeros_count = 0;
//     info.zeros_count = 0;
//     info.row = false;
//     while (j < a.columns)
//     {
//         i = 0;
//         curr_zeros_count = 0;
//         while (i < a.rows)
//         {
//             if (!a.matrix[i][j])
//                 curr_zeros_count++;
//             i++;
//         }
//         if (curr_zeros_count > info.zeros_count)
//         {
//             info.zeros_count = curr_zeros_count;
//             info.index = j;
//         }
//         j++;
//     }
//     return (info);
// }