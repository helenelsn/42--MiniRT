/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normaps_getter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 01:30:27 by srapin            #+#    #+#             */
/*   Updated: 2023/12/17 00:06:55 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"


static t_normal_map *get_cliff_map(bool to_free)
{
	static t_normal_map *map;
	static bool flag;
	
	if (to_free)
	{
		if (map)
			free(map->pixels);
		return NULL;
	}
	if (!map)
	{
		map = ft_calloc(1, sizeof(t_normal_map));
		flag = construct_map(map, "./normal_maps/cliff");
		if (!flag)
		{
			free(map);
			map = NULL;
		}
	}
	if (!flag)
		return NULL;
	return map;
}

static t_normal_map *get_sand_map(bool to_free)
{
	static t_normal_map *map;
	static bool flag;
	
	if (to_free)
	{
		if (map)
			free(map->pixels);
		return NULL;
	}
	if (!map)
	{
		map = ft_calloc(1, sizeof(t_normal_map));
		flag = construct_map(map, "./normal_maps/sand");
		if (!flag)
		{
			free(map);
			map = NULL;
		}
	}
	if (!flag)
		return NULL;
	return map;
}

static t_normal_map *get_terrain_map(bool to_free)
{
	static t_normal_map *map;
	static bool flag;
	
	if (to_free)
	{
		if (map)
			free(map->pixels);
		return NULL;
	}
	if (!map)
	{
		map = ft_calloc(1, sizeof(t_normal_map));
		flag = construct_map(map, "./normal_maps/terrain");
		if (!flag)
		{
			free(map);
			map = NULL;
		}
	}
	if (!flag)
		return NULL;
	return map;
}

static t_normal_map *get_tree_map(bool to_free)
{
	static t_normal_map *map;
	static bool flag;
	
	if (to_free)
	{
		if (map)
			free(map->pixels);
		return NULL;
	}
	if (!map)
	{
		map = ft_calloc(1, sizeof(t_normal_map));
		flag = construct_map(map, "./normal_maps/tree");
		if (!flag)
		{
			free(map);
			map = NULL;
		}
	}
	if (!flag)
		return NULL;
	return map;
}

static t_normal_map *get_wood_map(bool to_free)
{
	static t_normal_map *map;
	static bool flag;
	
	if (to_free)
	{
		if (map)
			free(map->pixels);
		return NULL;
	}
	if (!map)
	{
		map = ft_calloc(1, sizeof(t_normal_map));
		flag = construct_map(map, "./normal_maps/wood");
		if (!flag)
		{
			free(map);
			map = NULL;
		}
	}
	if (!flag)
		return NULL;
	return map;
}

t_normal_map *get_map_from_type(t_normap_type t)
{
	if (t == cliff)
		return get_cliff_map(false);
	if (t == sand)
		return get_sand_map(false);
	if (t == terrain)
		return get_terrain_map(false);
	if (t == wood)
		return get_wood_map(false);
	if (t == tree)
		return get_tree_map(false);
	return (NULL);
	
}

t_normal_map *erase_maps(t_normap_type t)
{
	if (t == cliff)
		return get_cliff_map(true);
	if (t == sand)
		return get_sand_map(true);
	if (t == terrain)
		return get_terrain_map(true);
	if (t == wood)
		return get_wood_map(true);
	if (t == tree)
		return get_tree_map(true);
	return (NULL);
	
}