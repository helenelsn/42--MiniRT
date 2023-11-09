/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:55:20 by srapin            #+#    #+#             */
/*   Updated: 2023/11/09 20:25:50 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mini_rt.h"
#include "../inc/bsp.h"


int main(int argc, char **argv)
{
    // t_vlist *garbage;
    t_app   app;
    ft_bzero(&app, sizeof(t_app));
    parse(argc, argv, &app.garbage, &app.p_data);
    
   
    t_bsp_node  root;
    t_vlist     planes;
    ft_memset(&root, 0, sizeof(t_bsp_node));
    ft_memset(&planes, 0, sizeof(t_vlist));

// passer l adresse de app.p_data.objects ?
    set_planes_list(app.p_data.objects, &planes);
    
    build_kd_tree(&root, app.p_data.objects);
    
    print_kd_tree(&root);
    
    
}