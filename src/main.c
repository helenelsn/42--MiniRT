/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:55:20 by srapin            #+#    #+#             */
/*   Updated: 2023/11/08 23:02:24 by hlesny           ###   ########.fr       */
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
    
   
    t_bsp_node root;
    ft_memset(&root, 0, sizeof(t_bsp_node));
    
    build_kd_tree(&root, app.p_data.objects);
    
    print_kd_tree(&root);
    
    
}