/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:55:08 by srapin            #+#    #+#             */
/*   Updated: 2023/12/10 2 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
#define STRUCT_H
// #include "mini_rt.h"



/* -------------------- PARSING AND GEOMETRICAL BASICS ------------------ */

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
} t_point;


typedef struct s_vec_3d
{
    double x;
    double y;
    double z;
    double norm;
} t_vec;

typedef struct  s_droite
{
    t_point  p;
    t_vec    v;
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

typedef enum e_parse_error
{
    none,
    invalid_args_nb,
    file,
    file_content,
    
} t_parse_error;


/* ------------------ INTERSECTIONS -------------------- */

typedef struct s_quadratic
{
	double	a;
	double	b;
	double	c;
	double	t_1;
	double	t_2;
}				t_quadratic;


/* ------------ MATERIALS SHARED PROPERTIES, OBJECTS STRUCTURE ------------- */

typedef union           u_color
{
    int                 hex;
    struct
    {
        unsigned char   b;
        unsigned char   g;
        unsigned char   r;
        unsigned char   t;
    };
}                       t_color;

/* bounding volume */
typedef struct  s_bbox_description
{
    /* Points ou vecteurs ? */ 
    t_point     min;
    t_point     max;
    double      width;
    double      height;
    double      length;
    double      surface_area;
}               t_bbox_description;

typedef struct  s_raytracing_material
{
    t_color             color;
    double              specular;
    double              reflective;               
    t_bbox_description  bbox;
}               t_raytracing_material;

typedef struct s_vlist
{
    void *			        content;
    t_raytracing_material   material;
    t_type                  type;
	struct s_vlist	        *next;
    void                    (*free_foo)(void *);
} t_vlist;



/* ------------------------------- RAYS --------------------------------- */

typedef struct  s_interval
{
    double  min;
    double  max;
}               t_interval;

#include <stdbool.h>

typedef struct	s_hit_info
{
	t_type 					obj_type;
	t_raytracing_material	obj_mat;
    void                    *obj_content;
	t_point				    hit_point;
	t_vec				    outward_normal;
    t_vec                   texture_normal; // bump mapping
	t_vec				    reflected_ray;
	double					distance; // ray_origin - object distance. set a -1 si le rayon n intersecte pas d objects
    double                  coef;
    t_color                 color;
    bool                    cap_hit;
}				t_hit_info;

typedef struct	s_ray
{
	t_point	    origin;
	t_vec	    direction;
	t_hit_info	hit_info;
}				t_ray;




/* ------------------------------ LIGHTS -------------------------------- */

/* Idealement, the intensities conveniently add up to 1.0.
    Because of the way the lighting equation works, 
    this ensures that no point can have a light intensity greater than this value.
    This means we won’t have any “overexposed” spots. */
typedef struct  s_light_infos
{   
    double      ratio;
    t_color     color;
}               t_light_info;

typedef struct s_mood_light
{
    t_light_info            infos;
}   t_mood_light;


typedef struct s_light
{
    t_point p;
    t_light_info            infos;
    struct s_light          *next;
}   t_light;




/* ------------------------- GEOMETRIC ELEMENTS ------------------------- */

typedef struct s_sphere
{
    t_point  p;
    double      radius;
}   t_sphere;

typedef struct s_plan
{
    t_point  p;
    t_vec    vec;
    
    double      a;
    double      b;
    double      c;
    double      d;
}   t_plan;

typedef struct  s_matrix
{
    int     rows;
    int     columns;
    double  **matrix;
}               t_matrix;


typedef struct s_cylindre
{
    t_point  p;
    t_vec    vec;
    t_vec    n0;
    t_vec    n1;
    double      radius;
    double      height;
    struct  s_matrix *base_to_cyl;
    struct  s_matrix *cyl_to_base;
    t_vec       p_to_origin;
    t_vec       origin_to_p;
    t_plan      cover_planes[2];
}   t_cylindre;

typedef struct  s_circle
{
    t_plan p;
    t_point  center;
    double      radius;
}              t_circle;

typedef struct  s_cone
{
    t_point  p;
    t_point  top;
    t_vec    vec;
    t_vec    n0;
    t_vec    n1;
    double      radius;
    double      height;
    struct  s_matrix *base_to_cyl;
    struct  s_matrix *cyl_to_base;
    t_vec       p_to_origin;
    t_vec       origin_to_p;
    t_plan      cover_plane;

    // t_circle    base;
    double      slant_height; /* hauteur oblique, calculée avec pythagore */
}               t_cone;

typedef struct  s_moebius
{
    double                  twists_count;
    /* quoi d'autre pour le définir ? */
}               t_moebius;



/* ---------------------------- BSP TREE ----------------------------   */

typedef enum    e_node_type
{
    node,
    leaf  
}               t_node_type;

typedef enum    e_dim
{
    x,
    y,
    z,
    no_axis
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
    int                 depth;
    
    t_bbox_description  bbox; // pas utile, se débrouiller pour l'enlever
    t_dim               split_dim; // pas utile, est dans split_inf
    t_split_infos       split_inf; 
    
    struct s_vlist      *items; /* NULL when not a leaf */
    int                 items_count; /* 0 when not a leaf */
    
    struct s_bsp_node   *parent; // ou autre si utilise les neighbor links
    struct s_bsp_node   *left;
    struct s_bsp_node   *right;
}               t_bsp_node;




/* ---------------------------- MLX DATA ----------------------------*/

typedef struct s_image
{
	void			*img;
	char			*addr;
	int				bpp;
	int				line_length;
	int				endian;
}					t_image;

typedef struct  s_mlx_data
{
    t_image			image;
    void		    *mlx_ptr;
	void		    *win_ptr;
     int            elem_selected;
    int            point_pushed;
    t_hit_info      elem_hit;
    double          after_dot;
    double          n;
}               t_mlx_data;

/* ---------------------------- CAMERA, FRAME ---------------------------- */

typedef struct  s_referentiel
{
    t_point  origin;
    t_vec    u;
    t_vec    v;
    t_vec    w;
}               t_referentiel;

typedef struct s_camera
{
    t_point      p;
    t_vec        direction;
    int             fov;
    t_referentiel   ref;
    
    // camera frame basis vectors 
    //t_vec    u;
    //t_vec    v;
    //t_vec    w;
}   t_camera;

typedef struct  s_viewport
{
    int         height;
    int         width;

   /*  t_vec    u;
    t_vec    v;
    t_vec    w; */
    
    t_point  pixel_00; // up-left pixel coordinates
    t_vec    pixel_delta_u;  // Offset to pixel to the right
    t_vec    pixel_delta_v;  // Offset to pixel below

    // pas encore sure d'ou ca s'applique exactement
    t_vec    defocus_disk_u; // Defocus disk horizontal radius
    t_vec    defocus_disk_v; // Defocus disk vertical radius
}               t_viewport;

/* ----------------------- MAIN DATA STRUCTURES ---------------------- */

typedef struct s_parsing_data
{
    t_camera        *cam;
    t_mood_light    *mooooo; // batarde j avais pas vu (drole)
    t_light         *lights;
    t_vlist         *objects;
    t_vlist         *planes;
} t_parsing_data;

typedef struct s_app
{
    t_parsing_data  p_data;
    t_viewport      frame;
    double          aspect_ratio;
    t_color         background;
    t_vlist         *garbage;
    t_vlist         *planes;
    t_bsp_node      root;
    t_mlx_data      mlx_data;
} t_app;


#endif