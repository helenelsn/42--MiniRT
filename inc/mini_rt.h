/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:55:13 by srapin            #+#    #+#             */
/*   Updated: 2023/11/28 21:53:34 by srapin           ###   ########.fr       */
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
#define WINDOWS_HEIGHT 	    900
#define WINDOWS_WIDHT 	    1500

# define SCREEN_WIDTH       1400.0
# define SCREEN_HEIGHT      800.0
# define ASPECT_RATIO  	    16/9

# define SAMPLES_PER_PIXEL  5 // Count of random samples for each pixel
# define FOCUS_DIST		    1 //  // Distance camera - plan de projection

# define DEG_TO_RAD 	    180/M_PI 

# define BACKGROUND_COLOR   255 // idk

# define T_INF      0.00001 //new

#endif