/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:55:13 by srapin            #+#    #+#             */
/*   Updated: 2023/11/29 22:01:50 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H 
#define MINI_RT_H

# include "../libs/libft/ft_printf.h"
# include "../libs/libmatrices/inc/matrices.h"
# include "../libs/minilibx-linux/mlx.h"
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

# include "struct.h"
# include "foo.h"
# include "mlx_hooks.h"


#define EXIT_SUCCES 	    0
#define EXIT_FAILURE 	    1
#define EXIT_MLX_FAILURE    2
// #define WINDOWS_HEIGHT 	    900
// #define WINDOWS_WIDHT 	    1500

# define IMAGE_WIDTH       1400.0
# define IMAGE_HEIGHT      800.0

# define SAMPLES_PER_PIXEL  1 // Count of random samples for each pixel
# define FOCUS_DIST		    10 // arbitraire : tester les rendus avec differentes valeurs // Distance camera - plan de projection

# define DEG_TO_RAD 	    M_PI/180.0

# define BACKGROUND_COLOR   0xffffff

# define T_INF      0.00001 //new

# define T_EPSILON  0.001

#endif