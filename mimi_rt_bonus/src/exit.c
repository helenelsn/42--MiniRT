/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:38:52 by Helene            #+#    #+#             */
/*   Updated: 2023/12/21 00:27:30 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mini_rt_bonus.h"

void	free_lights(t_parsing_data *data)
{
	t_light	*current;
	t_light	*tmp;

	current = data->lights;
	if (data->mooooo)
		free(data->mooooo);
	data->mooooo = NULL;
	while (current)
	{
		tmp = current;
		current = current->next;
		free(tmp);
		tmp = NULL;
	}
}

void	free_vlist(t_vlist *list)
{
	t_vlist	*current;
	t_vlist	*tmp;

	current = list;
	while (current)
	{
		tmp = current;
		current = current->next;
		if (tmp->content)
		{
			free(tmp->content);
			tmp->content = NULL;
		}
		free(tmp);
		tmp = NULL;
	}
}

void	minirt_destroy_display(t_app *app)
{
	int	i;

	if (app->mlx_data.image.img)
		mlx_destroy_image(app->mlx_data.mlx_ptr, app->mlx_data.image.img);
	if (app->mlx_data.win_ptr)
		mlx_destroy_window(app->mlx_data.mlx_ptr, app->mlx_data.win_ptr);
	if (app->mlx_data.mlx_ptr)
		mlx_destroy_display(app->mlx_data.mlx_ptr);
	if (app->mlx_data.mlx_ptr)
		free(app->mlx_data.mlx_ptr);
	free_vlist(app->p_data.planes);
	free_vlist(app->p_data.objects);
	free_lights(&app->p_data);
	if (app->p_data.cam)
		free(app->p_data.cam);
	app->p_data.cam = NULL;
	i = 0;
	while (i < no_map)
		erase_maps(i++);
	exit(0);
}
