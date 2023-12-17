/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 05:28:20 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/17 05:28:57 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mini_rt.h"

void	parse_error_occured(t_parse_error e, int fd)
{
	ft_printf("Error %d\n", e);
	if (fd > -1)
		close(fd);
	exit(EXIT_FAILURE);
}

void	free_tab(void *arg)
{
	char	**tab;
	int		i;

	i = 0;
	tab = arg;
	if (!tab)
		return ;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

int	null_term_tab_len(void **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		i++;
	return (i);
}
