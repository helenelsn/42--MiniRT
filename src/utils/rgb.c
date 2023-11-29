/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 00:08:53 by srapin            #+#    #+#             */
/*   Updated: 2023/11/29 21:18:00 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

 int	create_rgb(unsigned char r, unsigned char g, unsigned char b)
{
	t_color	c;

	// printf("in %s, r = %d, g = %d, b = %d\n", __func__, r, g, b);

	c = (t_color){
		.r = r, .b = b, .g = g};
	return (c.hex);
}

bool	get_rgb(char *str,  int *c)
{
	int i = 0;
	bool flag;
	// int hex = 0;
	if (!str)
		return -1;
	char **sp;
	flag = true;
	sp = ft_split(str, ',');
	if (!sp || null_term_tab_len((void **) sp) != 3)
		flag=false;
	else 
	{
		while(i < 3)
		{
			if (!ft_strisint(sp[i]) || 0 > ft_atoi(str) || 255 < ft_atoi(str))
				flag = false;
			i++;
		}
		if (flag)
			*c = create_rgb(ft_atoi(sp[0]), ft_atoi(sp[1]), ft_atoi(sp[2]));
	}
	//printf("%s, {color.hex = %lu}\n", __func__, *c);
	free_tab(sp);
	return flag;
}