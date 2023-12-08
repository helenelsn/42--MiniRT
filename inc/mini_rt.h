/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:55:13 by srapin            #+#    #+#             */
/*   Updated: 2023/12/08 18:49:00 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H 
#define MINI_RT_H

# include "../libs/libft/ft_printf.h"
# include "../libs/libmatrices/inc/matrices.h"
# include "../libs/minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdio.h>
# include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include <float.h>
#include <limits.h>

# include <math.h>
#define _USE_MATH_DEFINES // pour M_PI askip

# include "struct.h"
# include "foo.h"
# include "bsp.h"
# include "mlx_hooks.h"


#define EXIT_SUCCES 	    0
#define EXIT_FAILURE 	    1
#define EXIT_MLX_FAILURE    2
// #define WINDOWS_HEIGHT 	    900
// #define WINDOWS_WIDHT 	    1500

# define IMAGE_WIDTH       1400.0
# define IMAGE_HEIGHT      800.0

# define SAMPLES_PER_PIXEL  1 // Count of random samples for each pixel
# define FOCUS_DIST		    1 // arbitraire : tester les rendus avec differentes valeurs // Distance camera - plan de projection
# define HITPOINT_OFFSET    1e-3 // tester diff valeurs

# define REBOUNDS_LIMIT	3

# define DEG_TO_RAD 	    M_PI/180.0

# define T_INF      0.00001 //new

#endif