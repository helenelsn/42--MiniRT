/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:55:08 by srapin            #+#    #+#             */
/*   Updated: 2023/10/19 01:29:22 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
#define STRUCT_H
#include "mini_rt.h"

typedef struct s_point_3d
{
    double x;
    double y;
    double z;
} t_point_3d;


typedef struct s_vec_3d
{
    double x;
    double y;
    double z;
} t_vec_3d;

typedef struct s_glist
{
    void *			content;
	struct s_glist	*next;
    void            (*free_foo)(void *);
} t_glist;

typedef enum e_parse_error
{
    none,
    invalid_args_nb,
    file,
    file_content,
    
} t_parse_error;

typedef struct s_mood_light
{
    int color;
    double rat;
}   t_mood_light;

typedef struct s_light
{
    t_point_3d p;
    double rat;
    int color;
}   t_light;

typedef struct s_sphere
{
    t_point_3d p;
    double diam;
    int color;
}   t_sphere;

typedef struct s_plan
{
    t_point_3d p;
    t_vec_3d    vec;
    int         color;
}   t_plan;

typedef struct s_cylindre
{
    t_point_3d p;
    t_vec_3d    vec;
    double      diam;
    double      height;
    int         color;
    
}   t_cylindre;

typedef struct s_camera
{
    t_point_3d p;
    t_vec_3d    vec;
    int         fov;
}   t_camera;

// typedef enum e_elem
// {
//     bad,
//     light,
    
// } t_elem;

typedef union u_color
{
        int                                     hex;
        struct
        {
                unsigned char   b;
                unsigned char   g;
                unsigned char   r;
                unsigned char   t;
        };
}                                               t_color;

#endif