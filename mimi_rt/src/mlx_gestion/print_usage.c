/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_usage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 18:31:04 by srapin            #+#    #+#             */
/*   Updated: 2023/12/17 21:40:27 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../../inc/mini_rt.h"

void	print_usage(int mute)
{
	if (mute)
		return ;
	printf("To change any object's property ");
	printf("you must select it by left-clicking on it.\n");
	printf("To de-select an object  right-click anywhere on the screen.\n");
	printf("If you ever get tired of this message,");
	printf("press M  for mute. Press M again to un-mute. \n\nResizing : \n");
	printf(" Spheres : number ('.' for decimals) followed by");
	printf("the 'enter' key will change the radius.\n");
	printf(" Cones and cylinders : start by pressing H ");
	printf("or R (height or radius) ");
	printf("followed by the desired number.\n\n");
	printf("Translations and rotations : \n");
	printf("Each takes place along one of the three axis.\n");
	printf("Increment the rotation/translation buffer for each");
	printf("coordinate by pressing X,Y and/or Z.\n");
	printf("Multiple presses are added up.\n");
	printf("To then translate use the Up and Down arrows.");
	printf("To rotate use the Right and Left arrows.\n\nCheckerboard :\n");
	printf("Press C.\n\nBump mapping :\nPress B (be patient ");
	printf("this might take some time...).\n");
	printf("Each keypress changes the object's texture to the next texture ");
	printf("among the 5 available.\n\n");
}
