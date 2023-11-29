void test_mat()
{
    // t_matrix *m_void = new_void_matrix(3, 4);
    // print_mat(m_void);
    // t_matrix *m_vararg = new_matrix_from_var_args(3, 4, 1.0, 2.0, 3.0, 4.0 ,5.0,6.0,7.0,8.0,9.0,10.0, 11.0, 12.0);

    // print_mat(m_vararg);
    // t_matrix *res_scal = scalar_product(m_vararg, -1);
    // print_mat(res_scal);

    t_matrix *a =  new_matrix_from_var_args(3, 3, 10.0,2.0,3.0,4.0,5.0,6.0, 7.0, 8.0, 90.0);
    t_matrix *b =  new_matrix_from_var_args(2, 2, 7.0,8.0,9.0,10.0,11.0,12.0);
    // t_matrix *c =  new_matrix_from_var_args(4, 4, 1.0, 2.0, 3.0, 3.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 42.0, 12.0, 13.0, 500.0, 15.0, 5.0);
    t_matrix *c =  new_matrix_from_var_args(4, 4, 1.0, 2.0, 3.0, 0.0, 5.0, 6.0, 7.0, 0.0, 9.0, 10.0, 42.0, 12.0, 13.0, 14.0, 15.0, 5.0);
    // t_matrix *r = matrix_product(a, b);
    // t_matrix *r = get_sub_matrix(a, 1, 0);
    double res = get_mat_det(c);
    printf("res = %f\n", res);
    // print_mat(matrix_product(b, a));
    // print_mat(a);
    // print_mat(r);
    // del_mat(m_void);
    // del_mat(m_vararg);
    // del_mat(res_scal);
    del_mat(a);
    del_mat(b);
    del_mat(c);
    // del_mat(r);
}


