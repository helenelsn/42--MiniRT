/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:55:20 by srapin            #+#    #+#             */
/*   Updated: 2023/11/08 22:51:33 by srapin           ###   ########.fr       */
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
    
}

int main(int argc, char **argv)
{
    // t_vlist *garbage;
    t_app   app;
    ft_bzero(&app, sizeof(t_app));
    parse(argc, argv, &app.garbage, &app.p_data);
    // 0,0,20 20 255,0,0
    // char **lol =[ "0,0,20"], "20", "255, 0, 0", NULL:
    
}