/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:33:38 by srapin            #+#    #+#             */
/*   Updated: 2023/12/17 04:33:20 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/matrices.h"

void	init_cofactor(t_cofactor_info *ret, bool flag)
{
	ret->row = flag;
	ret->index = 0;
	ret->zeros_count = 0;
}

t_cofactor_info	get_best_row(t_matrix *m)
{
	t_cofactor_info	ret;
	int				curr_zero;
	int				i;
	int				j;

	i = 0;
	init_cofactor(&ret, true);
	while (i < m->rows)
	{
		j = 0;
		curr_zero = 0;
		while (j < m->columns)
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
	return (ret);
}

t_cofactor_info	get_best_col(t_matrix *m)
{
	t_cofactor_info	ret;
	int				curr_zero;
	int				i;
	int				j;

	i = 0;
	init_cofactor(&ret, false);
	while (i < m->columns)
	{
		j = 0;
		curr_zero = 0;
		while (j < m->rows)
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
	return (ret);
}

t_cofactor_info	scan_mat(t_matrix *m)
{
	t_cofactor_info	r;
	t_cofactor_info	c;

	r = get_best_row(m);
	c = get_best_col(m);
	if (c.zeros_count > r.zeros_count)
		return (c);
	return (r);
}
