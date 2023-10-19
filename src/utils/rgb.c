/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 00:08:53 by srapin            #+#    #+#             */
/*   Updated: 2023/10/19 00:32:42 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

int	create_rgb(unsigned char r, unsigned char g, unsigned char b)
{
	t_color	c;

	c = (t_color){
		.r = r, .b = b, .g = g};
	return (c.hex);
}

int	get_rgb(char *str)
{
	int i = 0;
	int hex = 0;
	if (!str)
		return -1;
	char **sp;
	sp = ft_split(str, ',');
	if (!sp || null_term_tab_len((void **) sp) != 3)
		hex = -1;
	else 
	{
		while(i < 3)
		{
			if (!ft_strisint(sp[i]) || 0 > ft_atoi(str) || 255 < ft_atoi(str))
				hex = -1;
			i++;
		}
		if (!hex) //bizzare mais partique
			hex = create_rgb(ft_atoi(sp[0]), ft_atoi(sp[1]), ft_atoi(sp[2]));
	}
	free_tab(sp);
	return hex;
}