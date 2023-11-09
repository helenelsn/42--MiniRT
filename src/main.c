/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:55:20 by srapin            #+#    #+#             */
/*   Updated: 2023/11/09 01:37:44 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mini_rt.h"

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

    t_matrix *a =  new_matrix_from_var_args(2, 3, 1.0,2.0,3.0,4.0,5.0,6.0);
    t_matrix *b =  new_matrix_from_var_args(2, 2, 7.0,8.0,9.0,10.0,11.0,12.0);
    // t_matrix *r = matrix_product(a, b);
    t_matrix *r = get_sub_matrix(a, 1, 0);
    // print_mat(matrix_product(b, a));
    // print_mat(a);
    print_mat(r);
    // del_mat(m_void);
    // del_mat(m_vararg);
    // del_mat(res_scal);
    del_mat(a);
    del_mat(b);
    del_mat(r);
}

int main(int argc, char **argv)
{
    // t_vlist *garbage;
    t_app   app;
    test_mat();
    ft_bzero(&app, sizeof(t_app));
    parse(argc, argv, &app.garbage, &app.p_data);
    // 0,0,20 20 255,0,0
    // char **lol =[ "0,0,20"], "20", "255, 0, 0", NULL:
    
}