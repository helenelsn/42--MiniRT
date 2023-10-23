/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Helene <Helene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:55:13 by srapin            #+#    #+#             */
/*   Updated: 2023/10/23 15:30:39 by Helene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
#define MINI_RT_H

# include "../libs/libft/ft_printf.h"
# include "../libs/minilibx-linux/mlx.h"
# include "struct.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>

# include "foo.h"

#define EXIT_SUCCES 0
#define EXIT_FAILURE 1
#define WINDOWS_HEIGHT 1500
#define WINDOWS_WIDHT 1500

# define SCREEN_WIDTH   1400.0
# define SCREEN_HEIGHT  800.0
# define SCREEN_RATIO  16/9
# define FOCUS_DIST 1
# define DEG_TO_RAD 180/M_PI 

typedef struct s_image
{
	void			*img;
	char			*addr;
	int				bpp;
	int				line_length;
	int				endian;
}					t_image;

#endif