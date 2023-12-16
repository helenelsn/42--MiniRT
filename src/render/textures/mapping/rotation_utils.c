/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 02:17:07 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/16 16:23:43 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/struct.h"
#include "../../../../inc/mini_rt.h"

t_matrix	*rotation_matrix_from_angle(double angle, t_vec axis)
{
	t_matrix    *rot;
    float       c;
    float       s; 

    rot = new_void_matrix(3, 3);
    c = cosf(angle);
    s = sinf(angle);
    normalise(&axis);
    rot->matrix[0][0] = axis.x * axis.x * (float)(1.0 - c) + c;
    rot->matrix[0][1] = axis.x * axis.y * (float)(1.0 - c) - axis.z * s;
    rot->matrix[0][2] = axis.x * axis.z * (float)(1.0 - c) + axis.y * s;
    rot->matrix[1][0] = axis.y * axis.x * (float)(1.0 - c) + axis.z * s;
    rot->matrix[1][1] = axis.y * axis.y * (float)(1.0 - c) + c;
    rot->matrix[1][2] = axis.y * axis.z * (float)(1.0 - c) - axis.x * s;
    rot->matrix[2][0] = axis.x * axis.z * (float)(1.0 - c) - axis.y * s;
    rot->matrix[2][1] = axis.y * axis.z * (float)(1.0 - c) + axis.x * s;
    rot->matrix[2][2] = axis.z * axis.z * (float)(1.0 - c) + c;
    return rot;
}

double  get_rotation_angle(t_vec surface_normal, t_vec unit_vector)
{
    double dot_product;
    double norm_product;
    double cos_theta;
    double theta;

    dot_product = surface_normal.x * unit_vector.x + surface_normal.y * unit_vector.y + surface_normal.z * unit_vector.z;
    norm_product = get_v_norm(surface_normal) * get_v_norm(unit_vector);
	cos_theta = dot_product / norm_product;
    theta = acos(cos_theta);
    return (theta);
}

t_vec    rotate_relative_pos(t_vec surface_normal, t_point hit_point, t_point obj_p)
{
    t_vec       position;
    double		theta;
    t_matrix    *rotation_mat;
    t_vec       rot_axis;
    t_vec       unit_vector;

    position = get_directional_vect(obj_p, hit_point);
    if (!ft_is_equalsf(surface_normal.y, 1.f, FLT_EPSILON))
	{
        // t_vec unit_vector = {0, 1, 0};
        // double dot_product = surface_normal.x * unit_vector.x + surface_normal.y * unit_vector.y + surface_normal.z * unit_vector.z;
        // double norm_product = get_v_norm(surface_normal) * get_v_norm(unit_vector);
		// double cos_theta = dot_product / norm_product;
        // double theta = acos(cos_theta);
        
        unit_vector = (t_vec){0, 1, 0, 1};
        theta = get_rotation_angle(surface_normal, unit_vector);
        rot_axis = cross_product(unit_vector, surface_normal);
        rotation_mat = rotation_matrix_from_angle(-theta, rot_axis);
		position = change_base_of_vec(position, (t_vec){0,0,0,0}, rotation_mat);
        // position = vec_mat_product(position, rotation_mat);        
        del_mat(rotation_mat);
	}
    return (position);
}
