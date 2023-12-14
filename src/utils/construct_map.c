/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 23:26:42 by srapin            #+#    #+#             */
/*   Updated: 2023/12/14 23:49:36 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

void construct_map(t_normal_map *map, char *name)
{
	int fd = open(name, O_RDONLY);
	char *line;
	char **sp_line;
	line = get_next_line(fd);
	sp_line = ft_split(line, ' ');
	map->width = atof(sp_line[0]);
	map->height =atof( sp_line[1]);
	free_tab(sp_line);
	free(line);
	map->pixels = ft_calloc(map->height * map->height, sizeof(t_vec));
	// int i = 0;
	
	// while (i < map->height)
	// {
	// 	map->pixels
	// }
	line = get_next_line(fd);
	int i = 0;
	while(line && line[0] !='\n')
	{		
		sp_line = ft_split(line, ' ');
		// printf("%s$\n", sp_line[1]);
		t_vec tmp;
		tmp.x = atof( sp_line[0]);
		tmp.y = atof(sp_line[1]);
		tmp.z = atof(sp_line[2]);
		map->pixels[i] = tmp;
		free_tab(sp_line);
		free(line);
		i++;
		line = get_next_line(fd);
	}
}