/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_usage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 18:31:04 by srapin            #+#    #+#             */
/*   Updated: 2023/12/15 21:38:04 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

void print_elem_selected(int mute, t_type t)
{
    if (mute)
        return;
    printf("%s\n", __func__);
    // printf("Elem selected:\nto change elem motif c\nto change normal map use n \nto rotate object use x, y, or z  and then arrows\n");
}

void print_usage(int mute)
{
    if (mute)
        return;
    printf("%s\n", __func__);
}