/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:55:13 by srapin            #+#    #+#             */
/*   Updated: 2023/12/17 22:52:05 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_BONUS_H
# define MINI_RT_BONUS_H

# include "../../libs/libft/ft_printf.h"
# include "../../libs/libmatrices/inc/matrices.h"
# include "../../libs/minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <float.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include "foo_bonus.h"
# include "struct_bonus.h"

# define _USE_MATH_DEFINES
# define EXIT_SUCCES 0
# define EXIT_FAILURE 1
# define EXIT_MLX_FAILURE 2

# define IMAGE_WIDTH 1400.0
# define IMAGE_HEIGHT 800.0
# define SAMPLES_PER_PIXEL 1
# define FOCUS_DIST 5
# define HITPOINT_OFFSET 1e-7
# define REBOUNDS_LIMIT 3
# define T_INF 0.00001
# define CHECKERS_HEIGHT 20

# define BONUS_SIZE 4
# define SP_PL_ARG_SIZE 4
# define CO_CY_ARG_SIZE 6

# define THREADS_NB 10
# define KEY_ESC 65307

#endif