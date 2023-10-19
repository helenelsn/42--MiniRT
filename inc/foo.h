/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foo.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:55:16 by srapin            #+#    #+#             */
/*   Updated: 2023/10/19 17:58:57 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FOO_H
#define FOO_H
#include "struct.h"

//parse
double get_ratio(char *str);
bool	get_point(char *str, t_point_3d *p);
bool	get_vec(char *str, t_vec_3d *p);
int get_fov(char *str);
int	create_rgb(unsigned char r, unsigned char g, unsigned char b);
bool	get_rgb(char *str, int *color);
t_parse_error parse(int ac, char **av, t_glist **garbage);
void free_tab(void *arg);
int null_term_tab_len(void **tab);
t_glist				*ft_glstnew(void * content, void foo(void *));
void				ft_glstadd_front(t_glist **lst, t_glist *new);
int					ft_glstsize(t_glist *lst);
t_glist				*ft_glstlast(t_glist *lst);
void				ft_glstadd_back(t_glist **lst, t_glist *new);
void				ft_glstdelone(t_glist *lst);
void				ft_glstclear(t_glist **lst);
void				ft_glstiter(t_glist *lst, void (*f)(void *));
t_glist				*ft_glstmap(t_glist *lst, void *(*f)(void *),
						void (*del)(void *));

bool					ft_strisint(char *str);
bool					ft_strisfloat(char *str);
bool					ft_strisequal(char *s1, char *s2);

double					ft_atof(char *nptr);



t_camera *create_camera(char **tab, t_glist **garbage);
t_cylindre *create_cylindre(char **tab, t_glist **garbage);
t_light *create_light(char **tab, t_glist **garbage);
t_mood_light *create_mood_light(char **tab, t_glist **garbage);
t_plan *create_plan(char **tab, t_glist **garbage);
t_sphere *create_sphere(char **tab, t_glist **garbage);


#endif