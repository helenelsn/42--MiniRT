/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:55:23 by srapin            #+#    #+#             */
/*   Updated: 2023/12/16 15:04:53 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mini_rt.h"


void parse_error_occured(t_parse_error e, t_vlist **garbage, int fd)
{
    ft_printf("Error %d\n", e);
    if (fd > -1)
        close(fd);
    if (garbage)
        ft_vlstclear(garbage);
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
    free(tab);
}

int null_term_tab_len(void **tab)
{
    int i = 0;
    while (tab && tab[i])
        i++;
    return i;
}

void *add_obj(char **tab, t_vlist **garbage, int fd, t_parsing_data *data)
{
    void *elem;
    elem = NULL;
    
    if (ft_strisequal(tab[0], "A"))
        elem = create_mood_light(tab, garbage, data);
    else if (ft_strisequal(tab[0], "C"))
        elem = create_camera(tab, garbage, data);
    else if (ft_strisequal(tab[0], "L"))
        elem = create_light(tab, garbage, data);
    else if (ft_strisequal(tab[0], "sp"))
        elem = create_sphere(tab, garbage, data);
    else if (ft_strisequal(tab[0], "pl"))
        elem = create_plan(tab, garbage, data);
    else if (ft_strisequal(tab[0], "cy"))
        elem = create_cylindre(tab, garbage, data);
    else if (ft_strisequal(tab[0], "co"))
        elem = create_cone(tab, garbage, data);
    else
        parse_error_occured(file_content, garbage, fd);
    if (!elem)
        parse_error_occured(file_content, garbage, fd);
    return elem;
}

void parse_and_create(int fd, t_vlist **garbage, t_parsing_data *data)
{
    char *line;
    char **sp_line;

    line = get_next_line(fd);
    // printf("%s", line);
    if (!line)
        parse_error_occured(file, garbage, fd);
    while (line)
    {
        if (!line[0] || line[0]=='\n')
        {
            free(line);
            line = get_next_line(fd);
            continue;
        }
        sp_line = ft_split(line, ' ');
        // ft_vlstadd_back(garbage, ft_vlstnew(sp_line, free_tab, 0)); 
        free(line);
        if (!sp_line || !sp_line[0])
        {
            free_tab(sp_line);
            parse_error_occured(file_content, garbage, fd);
        }
        add_obj(sp_line, garbage, fd, data);
        free_tab(sp_line);
        line = get_next_line(fd);
        // printf("%s", line);
    }
    if (!data->cam || !data->lights)
        parse_error_occured(file, garbage, fd);
    close(fd);
    // ft_vlstclear(garbage);
}


t_parse_error parse(int ac, char **av, t_vlist **garbage, t_parsing_data *data)
{
    int fd;

    if (ac < 2)
	{
        parse_error_occured(invalid_args_nb, garbage, -1);
	}
    ft_memset(data, 0, sizeof(t_parsing_data));
    fd = get_file(av[1]);
    parse_and_create(fd, garbage, data);
    return none;
}