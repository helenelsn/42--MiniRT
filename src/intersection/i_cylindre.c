/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_cylindre.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 00:52:41 by srapin            #+#    #+#             */
/*   Updated: 2023/12/04 22:17:59 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"


// void    get_inter_for_cylindre(t_cylindre *c, t_droite d)
// {
//     //compute distance entre droites
//     t_droite c_dir;
//     double dist;

//     c_dir.p = c->p;
//     c_dir.v = c->vec;

//     dist = get_dist_between_droite(d, c_dir);

//     if (dist < 0 || dist > c->radius)
//         return ;// aucune intersection d' office;

//     // if  ->droite parrallele -> checker les disk

//     // else -> ????
//     //si dist > radius -> aucun
//     //si dist <= radius ->résoudre l'eq des 2 droites + calc les limites du cylindre
    
// }