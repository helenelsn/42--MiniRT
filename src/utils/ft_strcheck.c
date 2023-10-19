/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcheck.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 00:01:45 by srapin            #+#    #+#             */
/*   Updated: 2023/10/19 02:15:55 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

bool	ft_strisint(char *str)
{
	bool	flag;
	int		i;

	i = 0;
	flag = true;
	if (!str)
		return (false);
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i]!= '\n' )
			flag = false;
		i++;
	}
	return (flag);
}

bool	ft_strisfloat(char *str)
{
	bool	flag;
	bool	point;
	int		i;

	i = -1;
	flag = true;
	point = false;
	if (!str || !str[0])
		return (false);
	if (str[0] == '-')
		i++;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
		{
			if (str[i] == '.')
			{
				if (!point)
					point = true;
				else
					flag = false;
			}
			else
				flag = false;
		}
	}
	return (flag);
}

bool	ft_strisequal(char *s1, char *s2)
{
	if (!s1 && !s2)
		return (true);
	if (!s1 || !s2)
		return (false);
	if (ft_strlen(s1) != ft_strlen(s2))
		return (false);
	if (!ft_strnstr(s1, s2, ft_strlen(s1)))
		return (false);
	return (true);
}

