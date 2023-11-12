/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Helene <Helene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:55:08 by srapin            #+#    #+#             */
/*   Updated: 2023/11/12 18:44:11 by Helene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
#define STRUCT_H
// #include "mini_rt.h"


# define T_INF      0.00001 //new

// typedef struct s_vlist;


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
    double norm; /* ca fait tout couiller ? pense oas juste a ajouter dans la construction*/
} t_vec_3d;

typedef struct  s_droite
{
    t_point_3d  p;
    t_vec_3d    v;
}               t_droite;

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

/* bounding volume */
typedef struct  s_bbox_description
{
    /* Points ou vecteurs ? */ 
    t_point_3d  min;
    t_point_3d  max;
    double      width;
    double      height;
    double      length;
    double      surface_area;
}               t_bbox_description;

typedef struct  s_raytracing_material
{
    int                 color;
    int                 specular; /* -1 si matte */
    double              reflective; /* in [0, 1] */                 
    t_bbox_description  bbox; /* tout à 0 ou -1 si s'agit d'une source lumineuse ? */
}               t_raytracing_material;

typedef struct s_vlist
{
    void *			        content;
    t_raytracing_material   material;
    t_type                  type;
	struct s_vlist	        *next;
    void                    (*free_foo)(void *);
} t_vlist;

typedef enum e_parse_error
{
    none,
    invalid_args_nb,
    file,
    file_content,
    
} t_parse_error;

typedef struct  s_light_infos
{
    /* Idealement, the intensities conveniently add up to 1.0.
    Because of the way the lighting equation works, 
    this ensures that no point can have a light intensity greater than this value.
    This means we won’t have any “overexposed” spots. */
    double  intensity; // pareil que (brightness) ratio;
    int     color;
}               t_light_info;

typedef struct s_mood_light
{
    //t_light_info          infos;
    double                  ratio;
    int                     color;
    t_raytracing_material   material; // ?
}   t_mood_light;


typedef struct s_light
{
    t_point_3d p;
    //t_light_info          infos;
    double                  ratio;
    int                     color;
    t_raytracing_material   material; // ?
}   t_light;

typedef struct s_sphere
{
    t_point_3d              p;
    double                  radius;
    int                     color;
}   t_sphere;

typedef struct s_plan
{
    t_point_3d              p; // pas défini par 2 vecteurs plutot ? -> 
    t_vec_3d                vec;
    double a;
    double b;
    double c;
    double d;
    int                 color;
}   t_plan;

typedef struct s_cylindre
{
    t_point_3d              p;
    t_vec_3d                vec;
    double                  radius;
    double                  height;
    int                 color;
    
}   t_cylindre;

typedef struct  s_circle
{
    t_point_3d  center;
    double      radius;
}              t_circle;

typedef struct  s_cone
{
    t_circle             base;
    // t_point_3d              center;
    // double                  radius;
    double                  height;
    double                  slant_height; /* hauteur oblique, calculée avec pythagore */
    t_vec_3d                orientation; // ou direction
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

// typedef struct  s_toroid
// {
//     t_section_type          type; // ?
//     t_point_2d              center;
//     t_disk                  section_infos; // ?
//   
// }               t_toroid;

typedef struct  s_moebius
{
    double                  twists_count;
    /* quoi d'autre pour le définir ? */
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
    t_mood_light *mooooo; // batarde j avais pas vu (drole)
    t_light *lights;
    t_vlist *objects;
    t_vlist *planes;
} t_parsing_data;



// typedef enum e_elem
// {
//     bad,
//     light,
    
// } t_elem;

typedef enum    e_node_type
{
    node,
    leaf  
}               t_node_type;

typedef enum    e_dim
{
    x,
    y,
    z
}               t_dim;

typedef struct  s_split_infos
{
    t_dim   dim;
    double  split_coord;
    double  cost;
}               t_split_infos;



typedef struct s_bsp_node
{
    t_node_type         type; 
    int                 depth; // ?
    
    t_bbox_description  bbox;
    t_dim               split_dim; // ?
    t_split_infos       split_inf;
    
    struct s_vlist             *items; /* NULL when not a leaf */
    int                 items_count; /* 0 when not a leaf */
    
    struct s_bsp_node   *parent;
    struct s_bsp_node   *left;
    struct s_bsp_node   *right;
}               t_bsp_node;

typedef struct s_image
{
	void			*img;
	char			*addr;
	int				bpp;
	int				line_length;
	int				endian;
}					t_image;

typedef struct s_app
{
    t_parsing_data p_data;
    t_frame         frame; //represente la fenetre par laquell on regarde
    t_vlist         *garbage;
    t_bsp_node      root;
    t_vlist         *planes;
	t_image			image; //ln 
    void		    *mlx_ptr;
	void		    *win_ptr;
} t_app;

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