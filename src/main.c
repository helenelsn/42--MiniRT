/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:55:20 by srapin            #+#    #+#             */
/*   Updated: 2023/11/28 14:21:13 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mini_rt.h"
#include "../inc/bsp.h"

// void get_dist(t_camera *cam)
// {
    
// }

// void get_frame(t_app *app)
// {
//     //plus dur que je pensais
// }

void test_mat()
{
    // t_matrix *m_void = new_void_matrix(3, 4);
    // print_mat(m_void);
    // t_matrix *m_vararg = new_matrix_from_var_args(3, 4, 1.0, 2.0, 3.0, 4.0 ,5.0,6.0,7.0,8.0,9.0,10.0, 11.0, 12.0);

    // print_mat(m_vararg);
    // t_matrix *res_scal = scalar_product(m_vararg, -1);
    // print_mat(res_scal);

    t_matrix *a =  new_matrix_from_var_args(3, 3, 10.0,2.0,3.0,4.0,5.0,6.0, 7.0, 8.0, 90.0);
    t_matrix *b =  new_matrix_from_var_args(2, 2, 7.0,8.0,9.0,10.0,11.0,12.0);
    // t_matrix *c =  new_matrix_from_var_args(4, 4, 1.0, 2.0, 3.0, 3.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 42.0, 12.0, 13.0, 500.0, 15.0, 5.0);
    t_matrix *c =  new_matrix_from_var_args(4, 4, 1.0, 2.0, 3.0, 0.0, 5.0, 6.0, 7.0, 0.0, 9.0, 10.0, 42.0, 12.0, 13.0, 14.0, 15.0, 5.0);
    // t_matrix *r = matrix_product(a, b);
    // t_matrix *r = get_sub_matrix(a, 1, 0);
    double res = get_mat_det(c);
    printf("res = %f\n", res);
    // print_mat(matrix_product(b, a));
    // print_mat(a);
    // print_mat(r);
    // del_mat(m_void);
    // del_mat(m_vararg);
    // del_mat(res_scal);
    del_mat(a);
    del_mat(b);
    del_mat(c);
    // del_mat(r);
}






static int  initialise_mlx_datad(t_app *app)
{
    app->mlx_data.mlx_ptr = mlx_init();
    if (!app->mlx_data.mlx_ptr)
        return (EXIT_MLX_FAILURE);
    app->mlx_data.win_ptr = mlx_new_window(app->mlx_data.mlx_ptr, WINDOWS_WIDHT, WINDOWS_HEIGHT, "miniRT");
    if (!app->mlx_data.win_ptr)
    {
        mlx_destroy_display(app->mlx_data.mlx_ptr);
        free(app->mlx_data.mlx_ptr);
        return (EXIT_MLX_FAILURE);
    }
    app->mlx_data.image.img = mlx_new_image(app->mlx_data.mlx_ptr, WINDOWS_WIDHT, WINDOWS_HEIGHT);
    app->mlx_data.image.addr = mlx_get_data_addr(app->mlx_data.image.img, &(app->mlx_data.image.bpp), 
                        &(app->mlx_data.image.line_length), &(app->mlx_data.image.endian));
    return (1);
}


static int  minirt_get_started(t_app *app)
{
    if (!initialise_mlx_datad(app))
    {
        write(STDERR_FILENO, "Error : mlx initialisation.\n", 28);
        return (EXIT_MLX_FAILURE);
    }
    
    build_kd_tree(&app->root, app->p_data.objects);
    draw_scene(app);
    
    mlx_put_image_to_window(app->mlx_data.mlx_ptr, app->mlx_data.win_ptr,
        app->mlx_data.image.img, 0, 0); // 2 derniers a verif
        
    mlx_hook(app->mlx_data.win_ptr, 2, 1L << 0, key_press, app);
	mlx_hook(app->mlx_data.win_ptr, 33, 1L << 17, close_mlx, app);
	mlx_loop(app->mlx_data.mlx_ptr);
    
    // destroy and free data
    return (0);
}



int main(int argc, char **argv)
{
    t_app   app;
    
    ft_bzero(&app, sizeof(t_app));
    parse(argc, argv, &app.garbage, &app.p_data);
    // init_app(&app); ->attention planew ft_memset(&app->root, 0, sizeof(t_bsp_node));
    // ft_memset(planes, 0, sizeof(t_vlist));

    if (minirt_get_started(&app))
        return (EXIT_MLX_FAILURE);
    
    /* draw_scene(&app); */
    
    /* print_kd_tree(&app.root);
    printf("cuties but ecoanxious lol <3\n"); */
    
}