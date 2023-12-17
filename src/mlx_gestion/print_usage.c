/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_usage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 18:31:04 by srapin            #+#    #+#             */
/*   Updated: 2023/12/17 06:27:44 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

void	print_elem_selected(int mute, t_type t)
{
	(void)t;
	if (mute)
		return ;
	printf("%s\n", __func__);
}

/* 
ft_printf("arrow to modify offset\n + and - to manage iteration\n");
	ft_printf("mouse click to change julia's parameter\n");
	ft_printf("c and v to change color\n n to change fractal\n");
	ft_printf("i to add or remove color intside fractale \n");
	ft_printf("o to add or remove color outside fractale \n");
	ft_printf("r to reset, zoom, ffset and max_iterations\n");
	 */

void	print_usage(int mute)
{
	if (mute)
		return ;
	//printf("%s\n", __func__);
	
	printf("%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s", "To change any object's property, you must select it by left-clicking on it.\n", \
	"To de-select an object, right-click anywhere on the screen.\n", \
	"If you ever get tired of the 'print_elem_selected' display, press M, for mute. Press M again to un-mute. \n", \
	"Resizing : \n", \
	"\t Spheres : number ('.' for decimals) followed by the 'enter' key will change the radius.\n", \
	"\t Cones and cylinders : start by pressing H or R (height or radius), followed by the desired number.\n", \
	"Translations and rotations : \n", \
	"\t Each takes place along one of the three axis. \n\t Increment the rotation/translation buffer for each ", \
	"coordinate by pressing X, Y and/or Z. \n\t Multiple presses are added up.", \
	"\t To then translate, use the Up and Down arrows.", \
	"\t To rotate, use the Right and Left arrows.\n", \
	"Checkerboard :\n", \
	"\t Press C.\n", \
	"Bump mapping : \t Press B (be patient, this might take some time...).\n", \
	"\tEach keypress changes the object's texture to the next texture, among the 5 available.\n");
}
