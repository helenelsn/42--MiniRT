/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foo.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:55:16 by srapin            #+#    #+#             */
/*   Updated: 2023/11/08 19:31:07 by srapin           ###   ########.fr       */
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
int	create_rgb(unsigned char r, unsigned char g, unsigned char b);
bool	get_rgb(char *str, int *c);
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


void    get_inter_for_sphere(t_sphere *elem, t_droite d);
void    get_inter_for_plan(t_plan *p, t_droite d);

#endif