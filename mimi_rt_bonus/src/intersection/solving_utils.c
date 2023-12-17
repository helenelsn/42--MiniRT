/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solving_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:55:39 by Helene            #+#    #+#             */
/*   Updated: 2023/12/17 22:51:23 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt_bonus.h"

double	get_closest_point(double a, double b)
{
	if (a <= 0.0 && b <= 0.0)
		return (0.0);
	if (a <= 0.0)
		return (b);
	if (b <= 0.0)
		return (a);
	if (a < b)
		return (a);
	return (b);
}

bool	solve_quadratic_eq(t_quadratic *eq)
{
	double	delta;
	double	denom;

	delta = eq->b * eq->b - 4 * eq->a * eq->c;
	eq->t_1 = 0;
	eq->t_2 = 0;
	if (delta < 0.0)
		return (false);
	denom = (2 * eq->a);
	if (delta == 0.0)
	{
		eq->t_1 = -(eq->b / denom);
		eq->t_2 = eq->t_1;
	}
	else
	{
		eq->t_1 = (-eq->b + sqrt(delta)) / denom;
		eq->t_2 = (-eq->b - sqrt(delta)) / denom;
	}
	return (true);
}

int	solve_quadratic(t_quadratic *f)
{
	double	discr;
	double	res;

	discr = (f->b * f->b) - 4 * f->a * f->c;
	if (discr < 0.0)
		return (0);
	if (discr == 0.0)
	{
		f->t_1 = -0.5 * f->b / f->a;
		f->t_2 = f->t_1;
	}
	else
	{
		if (f->b > 0.0)
			res = -0.5 * (f->b + sqrt(discr));
		else
			res = -0.5 * (f->b - sqrt(discr));
		f->t_1 = res / f->a;
		f->t_2 = f->c / res;
	}
	return (1);
}
