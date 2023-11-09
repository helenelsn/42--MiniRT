/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 21:01:11 by Helene            #+#    #+#             */
/*   Updated: 2023/11/09 17:33:34 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



t_cofactor_info get_efficient_index(t_matrix a) 
{
    t_cofactor_info cr;
    t_cofactor_info cc;

    cr = scan_rows(a);
    cc = scan_columns(a);
    if (cr.zeros_count > cc.zeros_count)
        return (cr);
    return (cc);
}

// t_matrix    compute_cofactor_m(t_matrix a)
// {
    
// }

// double  compute_determinant(t_matrix a)
// {
    
// }

t_matrix  *inverse(t_matrix a)
{
    double      det;
    t_matrix    cofactor_mat;
    if (a.rows != a.columns)
        return (NULL);
    
    det = compute_determinant(a);
    if (!det)
        return (NULL);
    cofactor_mat = compute_cofactor_m(a);
    return NULL;
    return (scalar_product(transpose(cofactor_mat), 1/det));
}

bool    are_equals(t_matrix a, t_matrix b)
{
    int i;
    int j;
    
    if (a.columns != b.columns || a.rows != b.rows)
        return (false);
    i = 0;
    while (i < a.rows)
    {
        j = 0
        j = 0;;
        while (j < a.columns)
        {
            if (a.matrix[i][j] != b.matrix[i][j])
                return (false
        j = 0;
}
