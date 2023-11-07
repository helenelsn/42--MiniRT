// void	ft_intersect_ray_cylinder(t_shape *sh, t_ray *ray)
// {
// 	t_mat	tmp;
// 	t_argb	dot;
// 	t_pt	calc;
// 	t_argb	dist;
// 	int		ret;

// 	ft_cylinder_calc_one(sh, ray, &tmp, &dot);
// 	ft_cylinder_calc_two(&calc, ray, &tmp, &dot);
// 	if ((ret = ft_cylinder_calc_three(&calc, &dist, &dot, ray)) != 0)
// 		return ;
// 	if ((ret = ft_cylinder_calc_five(sh, &dist, &dot, ray)) != 0)
// 		return ;
// 	if ((fabs(calc.y + calc.x * dist.r)) < dist.a \
// 		&& (ray->lenght = dist.r + 0.001))
// 	{
// 		if (ft_dot_product(ray->dir, sh->n) > 0)
// 			ft_inv_norm(&sh->n);
// 		return ;
// 	}
// 	ray->lenght = -1;
// }