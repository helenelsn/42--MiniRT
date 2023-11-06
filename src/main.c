/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:55:20 by srapin            #+#    #+#             */
/*   Updated: 2023/11/05 21:54:15 by srapin           ###   ########.fr       */
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

int main(int argc, char **argv)
{
    // t_vlist *garbage;
    t_app   app;
    ft_memset(&app, 0, sizeof(t_app));
    parse(argc, argv, &app.garbage, &app.p_data);
    // 0,0,20 20 255,0,0
    // char **lol =[ "0,0,20"], "20", "255, 0, 0", NULL:
    
}