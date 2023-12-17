/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:44:06 by srapin            #+#    #+#             */
/*   Updated: 2023/12/17 04:21:23 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/matrices.h"

t_matrix	*new_matrix_from_var_args(int r, int c, ...)
{
	t_matrix	*m;
	va_list		ap;
	int			i;
	int			j;

	i = 0;
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
	return (m);
}

t_matrix	*new_matrix_from_tab(int r, int c, double **tab)
{
	t_matrix	*m;

	m = ft_calloc(1, sizeof(t_matrix));
	m->rows = r;
	m->columns = c;
	m->matrix = tab;
	return (m);
}

t_matrix	*new_void_matrix(int r, int c)
{
	t_matrix	*m;
	int			i;

	i = 0;
	m = ft_calloc(1, sizeof(t_matrix));
	m->rows = r;
	m->columns = c;
	m->matrix = ft_calloc(m->rows, sizeof(double *));
	while (i < m->rows)
	{
		m->matrix[i] = ft_calloc(m->columns, sizeof(double));
		i++;
	}
	return (m);
}

t_matrix	*copy_matrix(t_matrix *m)
{
	t_matrix	*new;
	int			i;
	int			j;

	i = 0;
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
	return (new);
}

t_matrix	*new_3x3_matrix_from_vec(t_vec v0, t_vec v1, t_vec v2, bool lign)
{
	t_matrix	*new;
	t_matrix	*new2;

	new = new_void_matrix(3, 3);
	new->matrix[0][0] = v0.x;
	new->matrix[1][0] = v0.y;
	new->matrix[2][0] = v0.z;
	new->matrix[0][1] = v1.x;
	new->matrix[1][1] = v1.y;
	new->matrix[2][1] = v1.z;
	new->matrix[0][2] = v2.x;
	new->matrix[1][2] = v2.y;
	new->matrix[2][2] = v2.z;
	if (lign)
	{
		new2 = transpose(new);
		del_mat(new);
		return (new2);
	}
	return (new);
}
