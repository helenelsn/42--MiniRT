/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Helene <Helene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:55:08 by srapin            #+#    #+#             */
/*   Updated: 2023/10/21 00:14:12 by Helene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
#define STRUCT_H
#include "mini_rt.h"


# define T_INF 0.00001 //new

typedef struct s_point2d
{
    double x;
    double y;
} t_point_2d;

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

typedef enum e_type
{
    camera,
    cylindre,
    light,
    mood_light,
    plan,
    point_3d,
    sphere,
    vec_3d,
    vlist,
    
} t_type;

typedef struct s_vlist
{
    void *			content;
    t_type          type;
	struct s_vlist	*next;
    void            (*free_foo)(void *);
} t_vlist;

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
    double intensity;
}   t_mood_light;

typedef struct s_light
{
    t_point_3d p;
    int color;
    double rat;
    double intensity;
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

typedef struct s_frame
{
    t_plan plan;
    t_point_3d c0;
    t_point_3d c1;
    t_point_3d c2;
    t_point_3d c3;

}   t_frame;

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

typedef struct s_parsing_data
{
    t_camera *cam;
    t_mood_light *moo;
    t_light *lig;
    t_vlist *obj;
} t_parsing_data;

typedef struct s_app
{
    t_parsing_data p_data;
    t_frame  frame; //represente la fenetre par laquell on regarde
    t_vlist *garbage;
} t_app;

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