/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:55:08 by srapin            #+#    #+#             */
/*   Updated: 2023/11/29 19:48:50 by hlesny           ###   ########.fr       */
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
} t_point_3d;


typedef struct s_vec_3d
{
    double x;
    double y;
    double z;
    double norm;
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
    unsigned int       color;
    int                 specular; /* todo + tard init a -1.  -1 si matte */
    double              reflective; /* todo + tard : init a 0. in [0, 1] */                 
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



/* ------------------------------- RAYS --------------------------------- */

# define RECURS_LIMIT	3

typedef struct	s_hit_info
{
	// autre chose ?
	t_type 					obj_type;
	t_raytracing_material	obj_mat;
    void                    *obj_content;
	t_point_3d				hit_point;
	t_vec_3d				hit_p_normal;
	t_vec_3d				reflected_ray; // V : vector from P (hit point) to camera
	double					distance; // ray_origin - object distance. set a -1 si le rayon n intersecte pas d objects
    double                  coef;
}				t_hit_info;

typedef struct	s_ray
{
	t_point_3d	origin;
	t_vec_3d	direction; // vecteur unitaire ou s'en blc ?
	t_hit_info	hit_info;
}				t_ray;




/* ------------------------------ LIGHTS -------------------------------- */

/* Idealement, the intensities conveniently add up to 1.0.
    Because of the way the lighting equation works, 
    this ensures that no point can have a light intensity greater than this value.
    This means we won’t have any “overexposed” spots. */
typedef struct  s_light_infos
{   
    double  ratio;
    unsigned int     color;
}               t_light_info;

typedef struct s_mood_light
{
    t_light_info            infos;
    // t_raytracing_material   material; // ?
}   t_mood_light;


typedef struct s_light
{
    t_point_3d p;
    t_light_info            infos;
    // t_raytracing_material   material; // ?
    struct s_light          *next;
}   t_light;




/* ------------------------- GEOMETRIC ELEMENTS ------------------------- */

typedef struct s_sphere
{
    t_point_3d  p;
    double      radius;
    unsigned int   color;
}   t_sphere;

typedef struct s_plan
{
    t_point_3d  p; // pas défini par 2 vecteurs plutot ? -> 
    t_vec_3d    vec;
    
    double      a;
    double      b;
    double      c;
    double      d;
    
    unsigned int   color;
}   t_plan;

typedef struct s_cylindre
{
    t_point_3d  p;
    t_vec_3d    vec;
    double      radius;
    double      height;
    unsigned int   color;
    
}   t_cylindre;

typedef struct  s_circle
{
    t_point_3d  center;
    double      radius;
}              t_circle;

typedef struct  s_cone
{
    t_circle    base;
    double      height;
    double      slant_height; /* hauteur oblique, calculée avec pythagore */
    t_vec_3d    orientation; // ou direction
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
}               t_mlx_data;

/* ---------------------------- CAMERA, FRAME ---------------------------- */

typedef struct s_frame
{
     // pas sur que c'est le meilleur moyen de rpz
    t_plan plan;
    t_point_3d c0;
    t_point_3d c1;
    t_point_3d c2;
    t_point_3d c3;

}   t_frame;

typedef struct  s_referentiel
{
    t_point_3d  origin;
    t_vec_3d    u;
    t_vec_3d    v;
    t_vec_3d    w;
}               t_referentiel;

typedef struct s_camera
{
    t_point_3d      p;
    t_vec_3d        direction;
    int             fov;
    t_referentiel   ref;
    
    // camera frame basis vectors 
    //t_vec_3d    u;
    //t_vec_3d    v;
    //t_vec_3d    w;
}   t_camera;

typedef struct  s_viewport
{
    int         height;
    int         width;

   /*  t_vec_3d    u;
    t_vec_3d    v;
    t_vec_3d    w; */
    
    t_point_3d  pixel_00; // up-left pixel coordinates
    t_vec_3d    pixel_delta_u;  // Offset to pixel to the right
    t_vec_3d    pixel_delta_v;  // Offset to pixel below

    // pas encore sure d'ou ca s'applique exactement
    t_vec_3d    defocus_disk_u; // Defocus disk horizontal radius
    t_vec_3d    defocus_disk_v; // Defocus disk vertical radius
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
    t_vlist         *garbage;
    t_vlist         *planes;
    t_bsp_node      root;
    t_mlx_data      mlx_data;
} t_app;

typedef union u_color
{
        unsigned int                           hex;
        struct
        {
                unsigned char   b;
                unsigned char   g;
                unsigned char   r;
                unsigned char   t;
        };
}                                               t_color;

#endif