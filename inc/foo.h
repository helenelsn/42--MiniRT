/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foo.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:55:16 by srapin            #+#    #+#             */
/*   Updated: 2023/10/18 23:48:26 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FOO_H
#define FOO_H
#include "struct.h"

//parse

t_parse_error parse(int ac, char **av, t_glist **garbage);
void free_tab(void *arg);

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

#endif