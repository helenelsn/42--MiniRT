/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:45:37 by srapin            #+#    #+#             */
/*   Updated: 2023/12/17 04:22:00 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/matrices.h"

void	del_mat(void *v)
{
	t_matrix	*m;
	int			i;

	i = 0;
	if (!v)
		return ;
	m = (t_matrix *)v;
	while (i < m->rows)
	{
		free(m->matrix[i]);
		i++;
	}
	free(m->matrix);
	free(m);
}
