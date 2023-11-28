/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_sampling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:03:40 by hlesny            #+#    #+#             */
/*   Updated: 2023/11/28 19:21:39 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/struct.h"
#include "../../inc/mini_rt.h"

/* ------------------- UTILS ---------------- */

double degrees_to_radians(double degrees) {
    return (degrees * M_PI / 180.0);
}

double random_double() {
    // Returns a random real in [0,1).
    return (rand() / (RAND_MAX + 1.0));
}

double random_double(double min, double max) {
    // Returns a random real in [min,max).
    return (min + (max-min)*random_double());
}

int random_int(int min, int max) {
    // Returns a random integer in [min,max].
    return ((int)(random_double(min, max+1)));
}


/*  ------------------------------------------- */