/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 23:26:42 by srapin            #+#    #+#             */
/*   Updated: 2023/12/17 21:41:11 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

int	init_map(t_normal_map *map, char *name)
{
	int		fd;
	char	*line;
	char	**sp_line;

	fd = open(name, O_RDONLY);
	if (fd == -1)
	{
		printf("Error while constructing map %s\n", name);
		return (fd);
	}
	line = get_next_line(fd);
	sp_line = ft_split(line, ' ');
	map->width = atof(sp_line[0]);
	map->height = atof(sp_line[1]);
	free_tab(sp_line);
	free(line);
	map->pixels = ft_calloc(map->height * map->height, sizeof(t_vec));
	return (fd);
}

bool	construct_map(t_normal_map *map, char *name)
{
	int		fd;
	int		i;
	char	*line;
	char	**sp_line;
	t_vec	tmp;

	fd = init_map(map, name);
	if (fd == -1)
		return (false);
	line = get_next_line(fd);
	i = 0;
	while (line && line[0] != '\n')
	{
		sp_line = ft_split(line, ' ');
		tmp.x = atof(sp_line[0]);
		tmp.y = atof(sp_line[1]);
		tmp.z = atof(sp_line[2]);
		map->pixels[i] = tmp;
		free_tab(sp_line);
		free(line);
		i++;
		line = get_next_line(fd);
	}
	free(line);
	return (true);
}

t_normal_map	*get_map_from_type(t_normap_type t)
{
	if (t == cliff)
		return (get_cliff_map(false));
	if (t == sand)
		return (get_sand_map(false));
	if (t == terrain)
		return (get_terrain_map(false));
	if (t == wood)
		return (get_wood_map(false));
	if (t == tree)
		return (get_tree_map(false));
	return (NULL);
}

t_normal_map	*erase_maps(t_normap_type t)
{
	if (t == cliff)
		return (get_cliff_map(true));
	if (t == sand)
		return (get_sand_map(true));
	if (t == terrain)
		return (get_terrain_map(true));
	if (t == wood)
		return (get_wood_map(true));
	if (t == tree)
		return (get_tree_map(true));
	return (NULL);
}
