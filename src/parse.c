/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:55:23 by srapin            #+#    #+#             */
/*   Updated: 2023/10/19 17:57:33 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mini_rt.h"


void parse_error_occured(t_parse_error e, t_glist **garbage, int fd)
{
    ft_printf("Error %d\n", e);
    if (fd > -1)
        close(fd);
    if (garbage)
        ft_glstclear(garbage);
    exit(EXIT_FAILURE);
}

int get_file(char *filename)
{
    int fd;
    int len;

    len = ft_strlen(filename);
    if (len < 3 || !ft_strisequal(filename + len - 3, ".rt"))
    {
        parse_error_occured(file, NULL, -1);
        
    }
    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        parse_error_occured(file, NULL, -1);
    }
    return fd;
}

void free_tab(void *arg)
{
    char **tab;
    int i = 0;

    tab = arg;   
    if (!tab)
        return;
    while(tab[i])
        free(tab[i++]);
    // free(tab);
}

int null_term_tab_len(void **tab)
{
    int i = 0;
    while (tab && tab[i])
        i++;
    return i;
}

void *get_obj(char **tab, t_glist **garbage, int fd)
{
    void *elem;
    elem = NULL;
    
    if (ft_strisequal(tab[0], "A"))
        elem = create_mood_light(tab, garbage);
    else if (ft_strisequal(tab[0], "C"))
        elem = create_camera(tab, garbage);
    else if (ft_strisequal(tab[0], "L"))
        elem = create_light(tab, garbage);
    else if (ft_strisequal(tab[0], "sp"))
        elem = create_sphere(tab, garbage);
    else if (ft_strisequal(tab[0], "pl"))
        elem = create_plan(tab, garbage);
    else if (ft_strisequal(tab[0], "cy"))
        elem = create_cylindre(tab, garbage);
    else
        parse_error_occured(file_content, garbage, fd);
    if (!elem)
        parse_error_occured(file_content, garbage, fd);
    return elem;
}

void parse_and_create(int fd, t_glist **garbage)
{
    char *line;
    char **sp_line;

    line = get_next_line(fd);
    printf("%s", line);
    if (!line)
        parse_error_occured(file, garbage, fd);
    while (line)
    {
        sp_line = ft_split(line, ' ');
        ft_glstadd_back(garbage, ft_glstnew(sp_line, free_tab)); 
        free(line);
        if (!sp_line || !sp_line[0])
            parse_error_occured(file_content, garbage, fd);
        get_obj(sp_line, garbage, fd);
        line = get_next_line(fd);
        printf("%s", line);
    }
    close(fd);
    ft_glstclear(garbage);
}


t_parse_error parse(int ac, char **av, t_glist **garbage)
{
    int fd;

    if (ac < 2)
	{
        parse_error_occured(invalid_args_nb, garbage, -1);
		
	}
    fd = get_file(av[1]);
    parse_and_create(fd, garbage);
    return none;
}