/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foo.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:55:16 by srapin            #+#    #+#             */
/*   Updated: 2023/11/29 17:54:20 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FOO_H
#define FOO_H
#include "struct.h"

//parse
double get_ratio(char *str);
bool	get_point(char *str, t_point_3d *p);
bool	get_vec_from_str(char *str, t_vec_3d *p);
t_vec_3d get_vec_from_point(t_point_3d p, t_point_3d q);
double get_dist_between_points(t_point_3d p, t_point_3d q);
double get_dist_droite_point(t_droite d, t_point_3d p);
double get_dist_between_droite(t_droite d, t_droite e);
int get_fov(char *str);
unsigned int	create_rgb(unsigned char r, unsigned char g, unsigned char b);
bool	get_rgb(char *str, unsigned int *c);
t_parse_error parse(int ac, char **av, t_vlist **garbage, t_parsing_data *data);
void free_tab(void *arg);
int null_term_tab_len(void **tab);
t_vlist				*ft_vlstnew(void * content, void foo(void *), t_type t);
void				ft_vlstadd_front(t_vlist **lst, t_vlist *new);
int					ft_vlstsize(t_vlist *lst);
t_vlist				*ft_vlstlast(t_vlist *lst);
void				ft_vlstadd_back(t_vlist **lst, t_vlist *new);
void				ft_vlstdelone(t_vlist *lst);
void				ft_vlstclear(t_vlist **lst);
void				ft_vlst_del_in_list(t_vlist **lst, t_vlist *todel); // ln
void				ft_vlstiter(t_vlist *lst, void (*f)(void *));
t_vlist				*ft_vlstmap(t_vlist *lst, void *(*f)(void *),
						void (*del)(void *));
						

bool					ft_strisint(char *str);
bool					ft_strisfloat(char *str);
bool					ft_strisequal(char *s1, char *s2);

double					ft_atof(char *nptr);



t_camera *create_camera(char **tab, t_vlist **garbage, t_parsing_data *data);
t_cylindre *create_cylindre(char **tab, t_vlist **garbage, t_parsing_data *data);
t_light *create_light(char **tab, t_vlist **garbage, t_parsing_data *data);
t_mood_light *create_mood_light(char **tab, t_vlist **garbage, t_parsing_data *data);
t_plan *create_plan(char **tab, t_vlist **garbage, t_parsing_data *data);
t_sphere *create_sphere(char **tab, t_vlist **garbage, t_parsing_data *data);

void    compute_image(t_vlist *obj);

double vec_x_vec_scal(t_vec_3d v, t_vec_3d w);
t_vec_3d vec_x_vec_vectoriel(t_vec_3d v, t_vec_3d w);

double get_v_norm(t_vec_3d v);

t_vlist    	*get_inter(t_vlist *elem, t_droite d);
void    	get_inter_for_sphere(t_sphere *elem, t_droite d);
bool    	get_inter_for_plan(t_plan *p, t_droite d, t_point_3d *res);

/* -------------------- VEC POINT UTILS ------------------- */

double 		vect_get_coord(t_vec_3d v, int i);
double  	pt_get_coord(t_point_3d p, int i);
void    	pt_modify_coord(t_point_3d p, int i, double new_c);

t_point_3d	get_vec_coord(t_vec_3d v);

t_point_3d	point_double_multiply(double n, t_point_3d a);
t_point_3d	point_addition(t_point_3d a, t_point_3d b);
t_point_3d	point_substract(t_point_3d a, t_point_3d b);
void 		reset_point(t_point_3d *p, double a);
void 		set_point(t_point_3d *p, double x, double y, double z);
t_point_3d double_to_point(double a);
t_point_3d  translate_point(t_point_3d p, t_vec_3d u);

t_vec_3d	vect_double_multiply(double n, t_vec_3d a);
t_vec_3d	vect_addition(t_vec_3d a, t_vec_3d b);
t_vec_3d	vect_substract(t_vec_3d a, t_vec_3d b);
void    	normalise(t_vec_3d *v);
t_vec_3d	get_directional_vect(t_point_3d a, t_point_3d b);
t_vec_3d	get_unitary_dir_vect(t_point_3d a, t_point_3d b);
t_vec_3d 	get_unit_normal(t_hit_info hi, t_point_3d p);


/* -------------------- TRACE RAYS ---------------- */

void    	draw_scene(t_app *app);
double 		compute_lighting(t_app *app, float specular, t_ray ray);
t_vec_3d	get_incident_ray_of_light(t_vec_3d l, t_vec_3d n);

/*  ------- CHGT COORD, ANTI ALIASING ---------- */
t_vec_3d	pixel_sample(t_app *app, int x, int y);
void    	set_pixel_center(t_app *app, t_point_3d *pc, int x, int y);

/*  --------------- */

void    	copy_obj_properties(t_vlist *obj, t_hit_info *hinf, t_point_3d hp);
bool    	intersect(t_vlist *obj, t_ray *ray);

/*  --------- CAMERA ---------- */

void    	init_viewpoint(t_app *app);





/*  -------------------- MLX ------------------------ */

void 		init_app(t_app *app);
int 		close_mlx(void *app);

void		img_pixel_put(t_image image, int x, int y, int color);
void 		launch_app(t_app *arg);

#endif