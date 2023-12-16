/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:38:52 by Helene            #+#    #+#             */
/*   Updated: 2023/12/16 15:43:47 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/struct.h"
#include "../inc/mini_rt.h"
#include "../inc/bsp.h"

void    free_lights(t_app *app)
{
    t_light *current;
    t_light *tmp;

    current = app->p_data.lights;
    free(app->p_data.mooooo);
    app->p_data.mooooo = NULL;
    while (current)
    {
        tmp = current;
        current = current->next;
        free(tmp);
        tmp = NULL;
    }
}

void    free_vlist(t_vlist *list)
{
    t_vlist *current;

    current = list;
    while (current)
    {
        t_vlist *tmp = current;
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

void    minirt_destroy_display(t_app *app)
{
    mlx_destroy_image(app->mlx_data.mlx_ptr, app->mlx_data.image.img);
	mlx_destroy_window(app->mlx_data.mlx_ptr, app->mlx_data.win_ptr);
	mlx_destroy_display(app->mlx_data.mlx_ptr);
    free(app->mlx_data.mlx_ptr);
    free_vlist(app->p_data.planes);
    free_vlist(app->p_data.objects);
    free_lights(app);
    free(app->p_data.cam);
    app->p_data.cam = NULL;
}
