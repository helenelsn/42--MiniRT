/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:55:20 by srapin            #+#    #+#             */
/*   Updated: 2023/11/28 21:50:27 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mini_rt.h"
#include "../inc/bsp.h"


static int  initialise_mlx_data(t_app *app)
{
    app->mlx_data.mlx_ptr = mlx_init();
    if (!app->mlx_data.mlx_ptr)
        return (EXIT_MLX_FAILURE);
    app->mlx_data.win_ptr = mlx_new_window(app->mlx_data.mlx_ptr, WINDOWS_WIDHT, WINDOWS_HEIGHT, "miniRT");
    // if (!app->mlx_data.win_ptr)
    // {
    //     mlx_destroy_display(app->mlx_data.mlx_ptr);
    //     free(app->mlx_data.mlx_ptr);
    //     return (EXIT_MLX_FAILURE);
    // }
    app->mlx_data.image.img = mlx_new_image(app->mlx_data.mlx_ptr, WINDOWS_WIDHT, WINDOWS_HEIGHT);
    app->mlx_data.image.addr = mlx_get_data_addr(app->mlx_data.image.img, &(app->mlx_data.image.bpp), 
                        &(app->mlx_data.image.line_length), &(app->mlx_data.image.endian));
    return (0);
}


static int  minirt_get_started(t_app *app)
{
    if (initialise_mlx_data(app))
    {
        write(STDERR_FILENO, "Error : mlx initialisation.\n", 28);
        return (EXIT_MLX_FAILURE);
    }
    
    build_kd_tree(&app->root, app->p_data.objects);
    draw_scene(app);
    
    printf("lol0\n");
    mlx_put_image_to_window(app->mlx_data.mlx_ptr, app->mlx_data.win_ptr,
        app->mlx_data.image.img, 0, 0); // 2 derniers a verif
    printf("lol");
    // set_img(app);

        
    add_hooks(app);
    // printf("HEY\n");
	mlx_loop(app->mlx_data.mlx_ptr);
    printf("HEY\n");
    // destroy and free data
    return (0);
}



int main(int argc, char **argv)
{
    t_app   app;
    
    ft_bzero(&app, sizeof(t_app));
    parse(argc, argv, &app.garbage, &app.p_data);

    if (minirt_get_started(&app)) //free les bails 
        return (EXIT_MLX_FAILURE);

}