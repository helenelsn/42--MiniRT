/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 15:55:39 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/16 17:35:24 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/mini_rt.h"
#include "../../../inc/struct.h"

/*  pour un point d'intersection P,
	n la normale a la surface de l'objet en ce point.
	et v le vecteur directeur de l'origine du rayon a P
*/
t_vec	reflect_ray(t_vec v, t_vec n)
{
	return (vect_substract(v, vect_double_multiply(2 * dot(v, n), n)));
}

/*  pour un point d'intersection P,
	n la normale a la surface de l'objet en ce point.
	et l le vecteur directeur de P a l'origine du rayon 
	R⃗ = 2N⃗ ⟨N⃗, L⃗⟩ −L⃗
*/
t_vec	get_incident_ray_of_light(t_vec l, t_vec n)
{
	return (vect_substract(vect_double_multiply(2 * dot(n, l), n), l));
}
