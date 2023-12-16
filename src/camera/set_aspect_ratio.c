/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_aspect_ratio.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 15:35:36 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/16 15:37:21 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/struct.h"
#include "../../inc/mini_rt.h"

void    set_aspect_ratio(t_app *app)
{
    double width;
    double height;
    
    width = fmax(1, IMAGE_WIDTH);
    height = fmax(1, IMAGE_HEIGHT);
    app->aspect_ratio = height / width;
}
