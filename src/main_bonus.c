/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 23:32:08 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/17 02:37:47 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mini_rt.h"

// void    set_screen_data(t_app *app)
// {
//     app->screen.image_width = fmax(1, IMAGE_WIDTH);
//     app->screen.image_height = fmax(1, IMAGE_HEIGHT);
//     app->screen.threads_amount = fmax(1, THREADS_NB);
//     app->screen.aspect_ratio = app->screen.image_height \
//         / app->screen.image_width;
//     app->screen.pixels_per_thread = ( app->screen.image_width \
//         *  app->screen.image_height) / app->screen.threads_amount;
// }

// void 	set_viewpoint_dimensions(t_app *app)
// {
//     app->frame.width = FOCUS_DIST * tan(deg_to_rad(app->p_data.cam->fov) * 0.5f) * 2;
//     app->frame.height = app->frame.width * app->aspect_ratio;
// }


t_renderer *init_threads(t_app *app)
{
    t_renderer  *threads;
    threads = ft_calloc(sizeof(t_renderer), THREADS_NB);
    if (!threads)
        return (NULL); 
    for (int i = 0; i < THREADS_NB; i++) // a tej
    {
        threads[i].id = i;
        threads[i].app = app; // ?
    }
    return (threads);
}

void    launch_threads(t_renderer *threads)
{
    int i;
    
    i = 0;
    while (i < THREADS_NB)
    {
        if(pthread_create(&threads[i].tid, NULL, draw_scene_routine, (void *)&threads[i]))
            write(STDERR_FILENO, "pthread_create() failed\n", 24);
        i++;
    }
}

void    join_threads(t_renderer *threads)
{
    for (int i = 0; i < THREADS_NB; i++)
    {
        if (pthread_join(threads[i].tid, NULL))
            write(STDERR_FILENO, "pthread_join() failed\n", 22);
    }
}

t_renderer*    redraw_bonus(t_app *app)
{
    t_renderer *threads = init_threads(app);
    if (!threads)
        return (NULL);
    launch_threads(threads);
    join_threads(threads);
    free(threads);
}

int  minirt_get_started_bonus(t_app *app)
{
    if (initialise_mlx_data(app))
    {
        write(STDERR_FILENO, "Error : mlx initialisation.\n", 28);
        return (EXIT_MLX_FAILURE);
    }
    // set_screen_data(app);
    set_aspect_ratio(app);
    init_viewpoint(app);
    ft_bzero(&app->background, sizeof(t_color));
    
    t_renderer *threads = init_threads(app);
    if (!threads)
        return (EXIT_FAILURE);
    launch_threads(threads);
    join_threads(threads);
    free(threads);
    // draw_scene_routine((void *) &threads[0]);
    mlx_put_image_to_window(app->mlx_data.mlx_ptr, app->mlx_data.win_ptr,
        app->mlx_data.image.img, 0, 0); 
    add_hooks(app);
    minirt_destroy_display(app);
    return (0);
}