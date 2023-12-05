/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 18:15:06 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/05 22:38:56 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/struct.h"
#include "../../inc/mini_rt.h"

/* ---------------------- NORMALS COMPUTATIONS ----------------------- */

/* need center coordinates */
//tocheck
t_vec	normal_to_sphere(void *obj, t_point p)
{
	t_sphere 	*sp;
	t_vec	normal;

	sp = obj;
	normal = get_directional_vect(sp->p, p);
	
	return (normal);
}

/* produit vectoriel de deux vecteurs generateurs du plan */
//tocheck
t_vec	normal_to_plan(void *obj, t_point p)
{
	t_plan 		*pl;
	
	pl = obj;
	return (pl->vec);
}

/* traduit en coord cylindriques, calcule la normale, puis reconvertit en 
coord cartesiennes (?) */
//todo
t_vec 	normal_to_cylinder(void *obj, t_point p)
{
	t_cylindre	*cyl;
	t_vec	normal;

	cyl = obj;

	return (normal);
}

//todo
t_vec	normal_to_cone(void *obj, t_point p)
{
	t_cone *cn;
	t_vec	normal;

	cn = obj;	

	return (normal);
}

/* computes the normal of a point p on a given object */
t_vec get_unit_normal(t_hit_info hi, t_point p)
{
	t_vec normal;

	if (hi.obj_type == sphere)
		normal = normal_to_sphere(hi.obj_content, p);
	else if (hi.obj_type == plan)
		normal = normal_to_plan(hi.obj_content, p);
	else if (hi.obj_type == cylindre)
		normal = normal_to_cylinder(hi.obj_content, p);
	else if (hi.obj_type == cone)
		normal = normal_to_cone(hi.obj_content, p);
	else
		;// ?
	
	normalise(&normal);
	return (normal);
}
