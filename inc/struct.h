/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:55:08 by srapin            #+#    #+#             */
/*   Updated: 2023/10/18 23:47:48 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
#define STRUCT_H
#include "mini_rt.h"

typedef struct s_glist
{
    void *			content;
	struct s_glist	*next;
    void            (*free_foo)(void *);
} t_glist;

typedef enum e_parse_error
{
    none,
    invalid_args_nb,
    file,
    file_content,
    
} t_parse_error;

typedef struct s_mood_light
{
    
}   e_mood_light;

typedef enum e_elem
{
    bad,
    light,
    
} t_elem;

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