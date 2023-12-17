/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foo.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:55:16 by srapin            #+#    #+#             */
/*   Updated: 2023/12/17 21:38:36 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FOO_H
# define FOO_H
# include "struct.h"

//-------------------------- CAMERA --------------------------------//
double			deg_to_rad(double degrees);
void			init_viewpoint(t_app *app);
void			set_aspect_ratio(t_app *app);

//------------------------ CREATE ELEM ------------------------------//
t_camera		*create_camera(char **tab, t_parsing_data *data);
t_cylindre		*create_cylindre(char **tab, t_parsing_data *data);
t_light			*create_light(char **tab, t_parsing_data *data);
t_mood_light	*create_mood_light(char **tab, t_parsing_data *data);
t_plan			*create_plan(char **tab, t_parsing_data *data);
t_sphere		*create_sphere(char **tab, t_parsing_data *data);
t_cone			*create_cone(char **tab, t_parsing_data *data);
void			set_cone_dep(t_cone *elem);
void			set_cylindre_dep(t_cylindre *elem);

//------------------------ DIST ------------------------------//
double			get_dist_between_droite(t_droite d, t_droite e);
double			get_dist_droite_point(t_droite d, t_point p);
double			get_dist_between_points(t_point p, t_point q);
double			ft_min_and_positiv(double a, double b);

//------------------------ VLIST ------------------------------//

t_vlist			*ft_vlstnew(void *content, void foo(void *), t_type t);
void			ft_vlstadd_front(t_vlist **lst, t_vlist *new);
int				ft_vlstsize(t_vlist *lst);
t_vlist			*ft_vlstlast(t_vlist *lst);
void			ft_vlstadd_back(t_vlist **lst, t_vlist *new);
void			ft_vlstdelone(t_vlist *lst);
void			ft_vlstclear(t_vlist **lst);
void			ft_vlst_del_in_list(t_vlist **lst, t_vlist *todel);
void			ft_vlstiter(t_vlist *lst, void (*f)(void *));
t_vlist			*ft_vlstmap(t_vlist *lst, void *(*f)(void *),
					void (*del)(void *));
t_vlist			*ft_vlstnew_with_mat(void *content, void foo(void *), t_type t,
					t_material mat);

//------------------------ MLX GESTION ------------------------------//
int				close_mlx(void *arg);
t_vec			*get_elem_vec(t_hit_info hit);
void			add_hooks(t_app *app);
void			my_mlx_pixel_put(t_image *img, int x, int y, int color);
void			launch_app(t_app *app);
t_hit_info		get_hit_info(t_app *app, t_point ray_origin, t_vec dir,
					int rebound_nb);
t_point			*get_elem_point(t_hit_info hit);

/* -------------------- VEC POINT UTILS ------------------- */

double			vect_get_coord(t_vec v, int i);
double			pt_get_coord(t_point p, int i);
void			pt_modify_coord(t_point p, int i, double new_c);

t_point			get_vec_coord(t_vec v);
t_point			point_double_multiply(double n, t_point a);
t_point			point_addition(t_point a, t_point b);
t_point			point_substract(t_point a, t_point b);
void			reset_point(t_point *p, double a);
void			set_point(t_point *p, double x, double y, double z);
t_point			double_to_point(double a);
t_point			translate_point(t_point p, t_vec u);
t_vec			vect_double_multiply(double n, t_vec a);
t_vec			vect_addition(t_vec a, t_vec b);
t_vec			vect_substract(t_vec a, t_vec b);
void			normalise(t_vec *v);
t_vec			get_directional_vect(t_point origin, t_point dest);
t_vec			get_unitary_dir_vect(t_point a, t_point b);
t_vec			get_unit_normal(t_hit_info hi, t_point p);
bool			construct_map(t_normal_map *map, char *name);

/* ------------------- INTERSECTIONS ------------------ */

bool			intersect(t_vlist *obj, t_ray *ray);
bool			intersect_plan(t_ray *ray, void *object);
bool			intersect_sphere(t_ray *ray, void *object);
bool			intersect_cylindre(t_ray *ray, void *object);
int				intersect_cylinder_covers(t_ray *ray, t_cylindre *cylinder,
					double *t, t_quadratic *f);
bool			solve_quadratic_eq(t_quadratic *eq);
double			get_closest_point(double a, double b);
t_point			get_ray_point(t_ray ray, double t);
void			set_eq(t_plan *p);

/* -------------------- RENDER ------------------- */

void			draw_scene(t_app *app);
t_color			trace_ray(t_app *app, t_point ray_origin, t_vec dir,
					int rebound_nb);
void			copy_obj_properties(t_vlist *obj, t_hit_info *hinf,
					t_hit_info to_copy);
void			no_tree_intersections(t_app *app, t_ray *ray, t_interval t);
t_color			compute_lighting(t_app *app, t_ray ray);

/* -------------------- shader ------------------ */

t_color			compute_lighting(t_app *app, t_ray ray);
bool			compute_diffuse(t_light *light, t_ray ray, t_color *color,
					t_ray obj_to_light);
void			compute_specular(t_light *light, t_ray ray, t_color *color,
					t_ray obj_to_light);
t_vec			get_incident_ray_of_light(t_vec l, t_vec n);
t_vec			reflect_ray(t_vec v, t_vec n);

/*  ------ camera, coordinates changes, anti-aliasing ------ */

t_vec			pixel_sample(t_app *app);
void			set_pixel_center(t_app *app, t_point *pc, int x, int y);

/* --------------- textures, color disruption -------------- */

t_point_2d		object_mapping(void *object, t_hit_info hit);
t_color			checker_color_at(void *object, t_hit_info hit);
void			set_checkerboard_map(t_checkers_map *map, t_type elem,
					t_color checker_color);
t_vec			get_normal_perturbation(t_hit_info hit, void *object);
t_vec			rotate_relative_pos(t_vec surface_normal, t_point hit_point,
					t_point obj_p);
double			get_rotation_angle(t_vec surface_normal, t_vec unit_vector);
t_matrix		*rotation_matrix_from_angle(double angle, t_vec axis);
t_point_2d		spherical_mapping(t_sphere *sp, t_point p);

/*  ------------------------ utils ------------------------- */

t_interval		get_interval(double min, double max);
double			f__mod_f(double a, int n);
bool			ft_is_equalsf(const float a, const float b,
					const float tolerance);
float			fmodf_positive(float dividend, float divisor);
t_color			color_scale(t_color color, double scale);
t_color			color_add(t_color c1, t_color c2);
t_color			color_mult(t_color c1, t_color c2);
void			minirt_destroy_display(t_app *app);
void			init_app(t_app *app);
int				close_mlx(void *app);
void			img_pixel_put(t_image image, int x, int y, int color);
void			print_usage(int mute);
int				handle_mouse(int keysym, int x, int y, t_app *app);
void			redraw(t_app *app);
void			deselect(t_app *app);
bool			set_bonus_options(t_material *mat, char **tab);
bool			set_checkers(char *str, bool *to_mod);
void			set_ray_infos(t_ray *ray, t_vec direction, t_point ray_origin);
void			set_specular_in_mat(void *content, t_material *mat, t_type t);
void			set_color_in_mat(void *content, t_material *mat, t_type t);
double			get_ratio(char *str);
bool			get_point(char *str, t_point *p);
bool			get_vec_from_str(char *str, t_vec *p);
t_vec			get_vec_from_point(t_point p, t_point q);
int				get_fov(char *str);
int				create_rgb(unsigned char r, unsigned char g, unsigned char b);
bool			get_rgb(char *str, t_color *c);
void			parse(int ac, char **av, t_parsing_data *data);
void			free_tab(void *arg);
int				null_term_tab_len(void **tab);
bool			ft_strisint(char *str);
bool			ft_strisfloat(char *str);
bool			ft_strisequal(char *s1, char *s2);
double			ft_atof(char *nptr);
void			compute_image(t_vlist *obj);
t_vec			normal_to_cap(t_vec dir_obj, t_point obj_p, t_point hit_p);
double			dot(t_vec v, t_vec w);
t_vec			cross_product(t_vec v, t_vec w);
double			get_v_norm(t_vec v);
t_point			change_base_of_point(t_point v, t_vec trans, t_matrix *rot);
t_vec			change_base_of_vec(t_vec v, t_vec trans, t_matrix *rot);
int				intersect_plane(t_ray *ray, t_plan *shape, double *t);
bool			intersect_cone(t_ray *ray, void *object);
int				intersect_circle(t_ray *ray, t_circle circle, double *t,
					double comp);
double			pow2(double n);
int				solve_quadratic(t_quadratic *f);
double			ft_min(double a, double b);
t_normal_map	*get_map_from_type(t_normap_type t);
void			init_mat(t_material *mat);
void			*draw_scene_routine(void *routine_data);
t_renderer		*init_threads(t_app *app);
int				minirt_get_started_bonus(t_app *app);
int				initialise_mlx_data(t_app *app);
int				get_final_pixel_color(t_app *app, int x, int y);
void			redraw_bonus(t_app *app);
t_normal_map	*erase_maps(t_normap_type t);
bool			ft_str_beggin_with(char *str, char *beg);
bool			ft_str_end_with(char *str, char *end);
void			init_mat(t_material *mat);
void			arrow_press(int keycode, t_app *app);
void			modify_orientation(int keycode, t_app *app);
void			find_obj_and_replace_mat(t_app *app);
void			set_coherence(t_app *app);
int				fill_double(int keycode, double *to_mod, bool point_pushed);
int				key_press(int keycode, t_app *app);
void			set_parse_error(t_parsing_data *data, t_parse_error e,
					char *line);
t_normal_map	*get_sand_map(bool to_free);
t_normal_map	*get_cliff_map(bool to_free);
t_normal_map	*get_terrain_map(bool to_free);
t_normal_map	*get_tree_map(bool to_free);
t_normal_map	*erase_maps(t_normap_type t);
t_normal_map	*get_wood_map(bool to_free);
void			free_lights(t_parsing_data *data);
void			free_vlist(t_vlist *list);

#endif