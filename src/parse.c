/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:55:23 by srapin            #+#    #+#             */
/*   Updated: 2023/12/17 05:28:55 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mini_rt.h"

int	get_file(char *filename)
{
	int	fd;
	int	len;

	len = ft_strlen(filename);
	if (len < 3 || !ft_strisequal(filename + len - 3, ".rt"))
	{
		parse_error_occured(file, -1);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		parse_error_occured(file, -1);
	}
	return (fd);
}

void	*add_obj(char **tab, int fd, t_parsing_data *data)
{
	void	*elem;

	elem = NULL;
	if (ft_strisequal(tab[0], "A"))
		elem = create_mood_light(tab, data);
	else if (ft_strisequal(tab[0], "C"))
		elem = create_camera(tab, data);
	else if (ft_strisequal(tab[0], "L"))
		elem = create_light(tab, data);
	else if (ft_strisequal(tab[0], "sp"))
		elem = create_sphere(tab, data);
	else if (ft_strisequal(tab[0], "pl"))
		elem = create_plan(tab, data);
	else if (ft_strisequal(tab[0], "cy"))
		elem = create_cylindre(tab, data);
	else if (ft_strisequal(tab[0], "co"))
		elem = create_cone(tab, data);
	else
		parse_error_occured(file_content, fd);
	if (!elem)
		parse_error_occured(file_content, fd);
	return (elem);
}

void	parse_and_create(int fd, t_parsing_data *data)
{
	char	*line;
	char	**sp_line;

	line = get_next_line(fd);
	if (!line)
		parse_error_occured(file, fd);
	while (line)
	{
		if (!line[0] || line[0] == '\n')
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		sp_line = ft_split(line, ' ');
		free(line);
		if (!sp_line || !sp_line[0])
		{
			free_tab(sp_line);
			parse_error_occured(file_content, fd);
		}
		add_obj(sp_line, fd, data);
		free_tab(sp_line);
		line = get_next_line(fd);
	}
	if (!data->cam || !data->lights)
		parse_error_occured(file, fd);
	close(fd);
}

t_parse_error	parse(int ac, char **av, t_parsing_data *data)
{
	int fd;

	if (ac < 2)
		parse_error_occured(invalid_args_nb, -1);
	ft_memset(data, 0, sizeof(t_parsing_data));
	fd = get_file(av[1]);
	parse_and_create(fd, data);
	return (none);
}
