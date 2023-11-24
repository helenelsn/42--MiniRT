/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:55:13 by srapin            #+#    #+#             */
/*   Updated: 2023/11/24 18:02:10 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
#define MINI_RT_H

# include "../libs/libft/ft_printf.h"
# include "../libs/libmatrices/inc/matrices.h"
# include "../libs/minilibx-linux/mlx.h"
# include "struct.h"
# include "bsp.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include <float.h>

# include "foo.h"

#define EXIT_SUCCES 	    0
#define EXIT_FAILURE 	    1
#define EXIT_MLX_FAILURE    2
#define WINDOWS_HEIGHT 	    1500
#define WINDOWS_WIDHT 	    1500

# define SCREEN_WIDTH       1400.0
# define SCREEN_HEIGHT      800.0
# define SCREEN_RATIO  	    16/9
# define FOCUS_DIST 	    1
# define DEG_TO_RAD 	    180/M_PI 

# define BACKGROUND_COLOR   255 // idk

# define T_INF      0.00001 //new

#endif