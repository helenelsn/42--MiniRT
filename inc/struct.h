/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:55:08 by srapin            #+#    #+#             */
/*   Updated: 2023/11/06 02:11:23 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
#define STRUCT_H
// #include "mini_rt.h"


# define T_INF      0.00001 //new

typedef struct s_point2d
{
    double x;
    double y;
} t_point_2d;

/* aura besoin de vecteurs 2d aussi ?  no idea*/

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
    double norm; /* ca fait tout couiller ? pense oas juste a ajouter dans la construction*/
} t_vec_3d;

typedef struct s_droite
{
    t_point_3d p;
    t_vec_3d v;
} t_droite;
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
    cone
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

/* bounding volume */
typedef struct  s_bbox_description
{
    /* Points ou vecteurs ?? */ 
    t_point_3d  min;
    t_point_3d  max;
    double      width;
    double      height;
    double      length;
    double      surface_area;
}               t_bbox_description;

typedef struct  s_raytracing_material
{
    int         color;
    t_bbox_description    bbox; /* tout à 0 ou -1 si s'agit d'une source lumineuse ? */
}               t_raytracing_material;

typedef struct s_mood_light
{
    // int     color;
    double  ratio;
    double  intensity;
    t_raytracing_material   material;
}   t_mood_light;


typedef struct s_light
{
    t_point_3d p;
    t_raytracing_material   material;
    double  ratio;
    double  intensity;
}   t_light;

typedef struct s_sphere
{
    t_point_3d              p;
    double                  radius;
    t_raytracing_material   material;
}   t_sphere;

typedef struct s_plan
{
    t_point_3d              p; // pas défini par 2 vecteurs plutot ? -> 
    t_vec_3d                vec;
    t_raytracing_material   material;
    double a;
    double b;
    double c;
    double d;
}   t_plan;

typedef struct s_cylindre
{
    t_point_3d              p;
    t_vec_3d                vec;
    double                  radius;
    double                  height;
    t_raytracing_material   material;
    
}   t_cylindre;

typedef struct  s_hyperboloid
{
    
    t_raytracing_material   material;
}               t_hyperboloid;

typedef struct  s_paraboloid
{
    
    t_raytracing_material   material;
}               t_paraboloid;

typedef struct  s_disk
{
    t_point_3d  center;
    double      radius;
}              t_disk;

typedef struct  s_cone
{
    t_disk                  base;
    double                  height;
    double                  slant_height; /* hauteur oblique, calculée avec pythagore */
    t_vec_3d                orientation; // ou direction
    t_raytracing_material   material;
}               t_cone;

/* forme de la section résultant de la coupe
du tore/toroid 
s'en blc en vrai non ? fera que avec des cercles
et basta */
typedef enum e_section_type
{
    circle,
    rectangle   
}       t_section_type;

typedef struct  s_toroid
{
    t_section_type          type; // ?
    t_point_2d              center;
    t_disk                  section_infos; // ?
    t_raytracing_material   material;
}               t_toroid;

typedef struct  s_moebius
{
    double                  twists_count;
    /* quoi d'autre pour le définir ? */
    t_raytracing_material   material;
}               t_moebius;



typedef struct s_frame
{
     // pas sur que c'est le meilleur moyen de rpz
    t_plan plan;
    t_point_3d c0;
    t_point_3d c1;
    t_point_3d c2;
    t_point_3d c3;

}   t_frame;

typedef struct s_camera
{
    t_point_3d p;
    t_vec_3d    direction;
    int         fov;
}   t_camera;

typedef struct s_parsing_data
{
    t_camera *cam;
    t_mood_light *mooooo;
    t_light *lights;
    t_vlist *objects;
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