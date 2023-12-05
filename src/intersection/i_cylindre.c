/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_cylindre.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 00:52:41 by srapin            #+#    #+#             */
/*   Updated: 2023/12/05 22:38:56 by srapin           ###   ########.fr       */
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



int    get_inter_for_cylindre(t_cylindre *cy, t_ray r, double *t0, double *t1)
{
    //compute distance entre droites
    t_droite c_dir;
    double dist;
    t_vec dir = r.direction;
    t_point pos = r.origin;
    t_point center = cy->p;
    double radius = cy->radius;
    

    double a = (dir.x * dir.x) + (dir.z * dir.z);
    double b = 2*(dir.x*(pos.x-center.x) + dir.z*(pos.z-center.z));
    double c = (pos.x - center.x) * (pos.x - center.x) + (pos.z - center.z) * (pos.z - center.z) - (radius*radius);
    
    double delta = b*b - 4*(a*c);
	if(fabs(delta) < 0.001) return -1.0; 
    if(delta < 0.0) return -1.0;
    
    double f = (-b - sqrt(delta))/(2*a);
    double g = (-b + sqrt(delta))/(2*a);
    double t;
    
    if (f>g) t = g;
    else t = f;
    return t;
    // double r = pos.y + t*dir.y;
    
    // if ((r >= center.y) && (r <= center.y + height))return t;
    // else return -1;













    // c_dir.p = cy->p;
    // c_dir.v = cy->vec;

    // dist = get_dist_between_droite(d, c_dir);

    // if (dist < 0 || dist > cy->radiusadius)
    //     return 0;// aucune intersection d' office;

    // n1ector n0 = normalize(crossProduct(cy->vec, (n1ector){1, 0, 0}));
    // n1ector n1 = crossProduct(cy->vec, n0);

    // Paramètres de l'équation quadratique
    // t_vec lol = get_directional_vect(r.origin , cy->p);
    // double a = dot(cy->n0, cy->n0) + dot(cy->n1, cy->n1);
    // double b = 2 * (dot(cy->n0, vec_minus_vec( lol,vect_double_multiply(  dot(lol, cy->vec), cy->vec ))) + dot(cy->n1, vec_minus_vec(lol , vect_double_multiply(dot(lol, cy->vec), cy->vec)    )));
    // double c = dot(     vec_minus_vec(   lol ,  vect_double_multiply(dot(lol, cy->vec), cy->vec ) ),  vec_minus_vec(lol , vect_double_multiply(dot(lol, cy->vec), cy->vec)) )- cy->radius * cy->radius * (dot(cy->n0, cy->n0) + dot(cy->n1, cy->n1));


    // double a = dot(cy->n0, cy->n0) + dot(cy->n1, cy->n1);
    // double b = 2 * (dot(cy->n0, vec_minus_vec( r.direction,vect_double_multiply(  dot(r.direction, cy->vec), cy->vec ))) + dot(cy->n1, vec_minus_vec(r.direction , vect_double_multiply(dot(r.direction, cy->vec), cy->vec)    )));
    // double c = dot(     vec_minus_vec(   r.direction ,  vect_double_multiply(dot(r.direction, cy->vec), cy->vec ) ),  vec_minus_vec(r.direction , vect_double_multiply(dot(r.direction, cy->vec), cy->vec)) )- cy->radius * cy->radius * (dot(cy->n0, cy->n0) + dot(cy->n1, cy->n1));

    // Discriminant de l'équation quadratique
    // double discriminant = b * b - 4 * a * c;

    // if (discriminant < 0) {
    //     // Pas d'intersection
    //     return 0;
    // } else {
    //     // Calcul des solutions de l'équation quadratique
    //     *t0 = (-b - sqrt(discriminant)) / (2 * a);
    //     *t1 = (-b + sqrt(discriminant)) / (2 * a);

    //     // cy->n1érifier que les solutions sont positives et dans la hauteur du cylindre
    //     // if ((*t1 >= 0 && *t1 <= cy->height) || (*t0 >= 0 && *t0 <= cy->height)) {
    //     if ((*t1 >= 0 ) || (*t0 >= 0)) {
    //         return 1;  // Intersection trouvée
    //     } else {
    //         return 0;  // Pas d'intersection dans la hauteur du cylindre
    //     }
    // }

    // t_vec n0;
    // t_vec n1;
    

    // double a =dot(n0, n0) + dot(n1, n1);
    // double b = 2 * (n0.x * (r.direction.x - cy->vec.x * dot(r.direction, cy->vec)) + n1.x * (r.direction.y - cy->vec.y * dot(r.direction, cy->vec)));
    // double c = (r.direction.x - cy->vec.x * dot(r.direction, cy->vec)) * (r.direction.x - cy->vec.x * dot(r.direction, cy->vec)) +
    //           (r.direction.y - cy->vec.y * dot(r.direction, cy->vec)) * (r.direction.y - cy->vec.y * dot(r.direction, cy->vec)) -
    //           cy->radiusadius * cy->radiusadius * (n0.x * n0.x + n1.x * n1.x);
    // // if  ->droite parrallele -> checker les disk

    // // else -> ????
    // // vec
    // //si dist > radius -> aucun
    // //si dist <= radius ->résoudre l'eq des 2 droites + calc les limites du cylindre
    // double discriminant = b * b - 4 * a * c;

    // if (discriminant < 0) {
    //     // Pas d'intersection
    //     return 0;
    // } else {
    //     // Calcul des solutions de l'équation quadratique
    //     *t1 = (-b - sqrt(discriminant)) / (2 * a);
    //     *t0 = (-b + sqrt(discriminant)) / (2 * a);

    //     // cy->n1érifier que les solutions sont positives et dans la hauteur du cylindre
    //     // if ((*t1 >= 0 && *t1 <= cy->height) || (*t0 >= 0 && *t0 <= cy->height)) {
    //     if ((*t1 >= 0) || (*t0 >= 0)) {
    //         // printf("heyy\n");
    //         return 1;  // Intersection trouvée
    //     } else {
    //         return 0;  // Pas d'intersection dans la hauteur du cylindre
    //     }
    // }
    return false;
}