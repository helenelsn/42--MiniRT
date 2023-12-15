/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:51:47 by Helene            #+#    #+#             */
/*   Updated: 2023/12/15 20:45:37 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/mini_rt.h"

t_hit_info    get_hit_info(t_app *app, t_point ray_origin, t_vec dir, int rebound_nb)
{
    t_ray		ray;
	t_vec	reflected_ray;
	t_color 	local_color;
	double 		reflected_color;
	
	ft_memset(&ray, 0, sizeof(t_ray)); // verifier que ca ecrase pas de la data que veut garder (jpense pas)
	set_ray_infos(&ray, dir, ray_origin);
	
	//ray_traversal_algo(&app->root, &ray);
	rec_ray_traverse(app, &ray, get_interval(HITPOINT_OFFSET, INFINITY));
	
	// no_tree_intersections(app->p_data, &ray, get_interval(HITPOINT_OFFSET, INFINITY));
	
	return (ray.hit_info);

}