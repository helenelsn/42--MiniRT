/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_object_material.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:52:57 by Helene            #+#    #+#             */
/*   Updated: 2023/12/14 16:03:11 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/struct.h"
#include "../../inc/mini_rt.h"

// void set_obj_material(void * content, t_material *mat, t_type t)
// {
//     if (mat->specular || mat->reflective || mat->color.hex)
//         return;
//     if (t == cylindre)
//     {
//         mat->color = ((t_cylindre *)content)->color;
//         mat->specular = ((t_cylindre *)content)->specular;
//         mat->reflective = ((t_cylindre *)content)->reflective;
//     }
//     if (t == plan)
//     {
//         mat->color = ((t_plan *)content)->color;
//         mat->specular = ((t_plan *)content)->specular;
//         mat->reflective = ((t_plan *)content)->reflective;
//     }
//     if (t == sphere)
//     {
//         mat->color = ((t_sphere *)content)->color;
//         mat->specular = ((t_sphere *)content)->specular;
//         mat->reflective = ((t_sphere *)content)->reflective;
//     }
//     // mat->color = 500;
// }

// void set_color_in_mat(void * content, t_material *mat, t_type t)
// {
//     if (mat->color.hex)
//         return;
//     if (t == cylindre)
//         mat->color = ((t_cylindre *)content)->color;
//     if (t == plan)
//         mat->color = ((t_plan *)content)->color;
//     if (t == sphere)
//         mat->color = ((t_sphere *)content)->color;
//     if (t == light)
//         mat->color = ((t_light *)content)->infos.color;
//     if (t == mood_light)
//         mat->color = ((t_mood_light *)content)->infos.color;
//     // mat->color = 500;
// }

// void set_specular_in_mat(void * content, t_material *mat, t_type t)
// {
//     if (mat->specular)
//         return;
//     if (t == cylindre)
//         mat->specular = ((t_cylindre *)content)->specular;
//     if (t == plan)
//         mat->specular = ((t_plan *)content)->specular;
//     if (t == sphere)
//     {
//         mat->specular = ((t_sphere *)content)->specular;
//         // printf("%f\n", mat->specular);
//     }
//     // mat->color = 500;
// }
// void set_reflective_in_mat(void * content, t_material *mat, t_type t)
// {
//     if (mat->reflective)
//         return;
//     if (t == cylindre)
//         mat->reflective = ((t_cylindre *)content)->reflective;
//     if (t == plan)
//         mat->reflective = ((t_plan *)content)->reflective;
//     if (t == sphere)
//     {
//         mat->reflective = ((t_sphere *)content)->reflective;
//         // printf("%f\n", mat->specular);
//     }
//     // mat->color = 500;
// }

void    copy_obj_properties(t_vlist *obj, t_hit_info *hit, t_hit_info to_copy)
{
    // set_color_in_mat(obj->content, &obj->material, obj->type);
	// set_specular_in_mat(obj->content, &obj->material, obj->type);
    // set_reflective_in_mat(obj->content, &obj->material, obj->type);
    // set_obj_material(obj->content, &obj->material, obj->type);
    
    hit->obj_content = obj->content;  // est-ce que couille si supprime l objet originel ?
    hit->obj_type = obj->type;
    hit->obj_mat = obj->material;
    hit->hit_point = to_copy.hit_point;
    hit->cap_hit = to_copy.cap_hit;
    
}