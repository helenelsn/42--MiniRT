/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:55:13 by srapin            #+#    #+#             */
/*   Updated: 2023/12/16 23:06:11 by hlesny           ###   ########.fr       */
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
#include <float.h>
#include <limits.h>
// #include <pthread.h>


# include <math.h>
#define _USE_MATH_DEFINES // pour M_PI askip

# include "struct.h"
# include "foo.h"
# include "bsp.h"
# include "mlx_hooks.h"

#define EXIT_SUCCES 	    0
#define EXIT_FAILURE 	    1
#define EXIT_MLX_FAILURE    2

# define IMAGE_WIDTH       1400.0
# define IMAGE_HEIGHT      800.0
# define SAMPLES_PER_PIXEL  1 // Count of random samples for each pixel
# define FOCUS_DIST		    5 // arbitraire : tester les rendus avec differentes valeurs // Distance camera - plan de projection
# define HITPOINT_OFFSET    1e-7 // tester diff valeurs
# define REBOUNDS_LIMIT	1
# define T_INF      0.00001 //new
# define CHECKERS_HEIGHT    20


# define    THREADS_NB  10

#define BONUS_SIZE 4
#define SP_PL_ARG_SIZE 4
#define CO_CY_ARG_SIZE 6

#endif