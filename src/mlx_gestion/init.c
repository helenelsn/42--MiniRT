/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 02:23:05 by srapin            #+#    #+#             */
/*   Updated: 2023/12/16 23:11:52 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || y > IMAGE_HEIGHT || x > IMAGE_WIDTH)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*( int *)dst = color;
}