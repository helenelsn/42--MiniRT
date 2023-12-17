/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 05:28:20 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/17 06:40:20 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mini_rt.h"

void	set_parse_error(t_parsing_data *data, t_parse_error e, char *line)
{
	data->err = e;
	printf("Error during parsing");
	if (e == invalid_args_nb)
		printf(": bad args nb\n");
	else if (e == cannot_open_file)
		printf(": can not open file\n");
	else if (e == file_content && line)
		printf("line :\n{%s}\nis not correctly formated\n", line);
	else if (e == missing_elem)
		printf(": necessary elem are missing\n");
	else
		printf("\n");
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
