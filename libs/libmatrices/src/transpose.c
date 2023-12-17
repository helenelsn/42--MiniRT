/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transpose.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 23:47:22 by srapin            #+#    #+#             */
/*   Updated: 2023/12/17 04:33:54 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/matrices.h"

t_matrix	*transpose(t_matrix *m)
{
	t_matrix	*res;
	int			i;
	int			j;

	res = new_void_matrix(m->columns, m->rows);
	i = 0;
	while (i < m->rows)
	{
		j = 0;
		while (j < m->columns)
		{
			res->matrix[j][i] = m->matrix[i][j];
			j++;
		}
		i++;
	}
	return (res);
}
