/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:55:20 by srapin            #+#    #+#             */
/*   Updated: 2023/12/16 21:24:40 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mini_rt.h"
#include "../inc/bsp.h"

static int  initialise_mlx_data(t_app *app)
{
    app->mlx_data.mlx_ptr = mlx_init();
    if (!app->mlx_data.mlx_ptr)
        return (EXIT_MLX_FAILURE);
    app->mlx_data.win_ptr = mlx_new_window(app->mlx_data.mlx_ptr, IMAGE_WIDTH, IMAGE_HEIGHT, "miniRT");
    if (!app->mlx_data.win_ptr)
    {
        mlx_destroy_display(app->mlx_data.mlx_ptr);
        free(app->mlx_data.mlx_ptr);
        return (EXIT_MLX_FAILURE);
    }
    app->mlx_data.image.img = mlx_new_image(app->mlx_data.mlx_ptr, IMAGE_WIDTH, IMAGE_HEIGHT);
    app->mlx_data.image.addr = mlx_get_data_addr(app->mlx_data.image.img, &(app->mlx_data.image.bpp), 
                        &(app->mlx_data.image.line_length), &(app->mlx_data.image.endian));
    return (0);
}

t_renderer *init_threads(t_app *app)
{
    t_renderer  *threads;
    threads = ft_calloc(sizeof(t_renderer), app->screen.threads_amount);
    if (!threads)
        return (NULL); 
    for (int i = 0; i < app->screen.threads_amount; i++) // a tej
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
    for (int i = 0; i < threads->app->screen.threads_amount; i++)
    {
        if (pthread_join(threads[i].tid, NULL))
            write(STDERR_FILENO, "pthread_join() failed\n", 22);
    }
}

static int  minirt_get_started(t_app *app)
{
    if (initialise_mlx_data(app))
    {
        write(STDERR_FILENO, "Error : mlx initialisation.\n", 28);
        return (EXIT_MLX_FAILURE);
    }
    set_screen_data(app);
    init_viewpoint(app);
    ft_bzero(&app->background, sizeof(t_color));
    
    t_renderer *threads = init_threads(app);
    if (!threads)
        return (EXIT_FAILURE);
    launch_threads(threads);
    join_threads(threads);
    
    mlx_put_image_to_window(app->mlx_data.mlx_ptr, app->mlx_data.win_ptr,
        app->mlx_data.image.img, 0, 0); 
    add_hooks(app);
    minirt_destroy_display(app);
    return (0);
}

int main(int argc, char **argv)
{
    t_app   app;
    
    ft_bzero(&app, sizeof(t_app));
    parse(argc, argv, &app.garbage, &app.p_data);
    if (minirt_get_started(&app))
        return (EXIT_MLX_FAILURE);
    return (0);
}