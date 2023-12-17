/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:55:23 by srapin            #+#    #+#             */
/*   Updated: 2023/12/17 20:50:37 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mini_rt.h"

int	get_file(char *filename)
{
	int	fd;
	int	len;

	len = ft_strlen(filename);
	if (len < 3 || !ft_strisequal(filename + len - 3, ".rt"))
		return (-1);
	fd = open(filename, O_RDONLY);
	return (fd);
}

void	*add_obj(char **tab, t_parsing_data *data, char *line)
{
	void	*elem;

	elem = NULL;
	if (ft_strisequal(tab[0], "A"))
		elem = create_mood_light(tab, data);
	else if (ft_strisequal(tab[0], "C"))
		elem = create_camera(tab, data);
	else if (!BONUS_SIZE && ft_strisequal(tab[0], "L"))
		elem = create_light(tab, data);
	else if (BONUS_SIZE && ft_strisequal(tab[0], "l"))
		elem = create_light(tab, data);
	else if (ft_strisequal(tab[0], "sp"))
		elem = create_sphere(tab, data);
	else if (ft_strisequal(tab[0], "pl"))
		elem = create_plan(tab, data);
	else if (ft_strisequal(tab[0], "cy"))
		elem = create_cylindre(tab, data);
	else if (ft_strisequal(tab[0], "co"))
		elem = create_cone(tab, data);
	if (!elem)
	{
		free_tab(tab);
		set_parse_error(data, file_content, line);
	}
	return (elem);
}

void	parse_and_create(int fd, t_parsing_data *data)
{
	char	*line;
	char	**sp_line;
	void	*elem;

	line = get_next_line(fd);
	while (line)
	{
		if (!line[0] || line[0] == '\n')
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		sp_line = ft_split(line, ' ');
		if (sp_line && sp_line[0] && sp_line[0][0] != '\n')
			elem = add_obj(sp_line, data, line);
		free(line);
		free_tab(sp_line);
		line = get_next_line(fd);
	}
	if (!data->cam || !data->lights)
		set_parse_error(data, missing_elem, NULL);
	close(fd);
}

void	parse(int ac, char **av, t_parsing_data *data)
{
	int	fd;

	if (ac < 2)
	{
		data->err = invalid_args_nb;
		return ;
	}
	ft_memset(data, 0, sizeof(t_parsing_data));
	data->line = -1;
	fd = get_file(av[1]);
	if (fd < 0)
	{
		set_parse_error(data, cannot_open_file, NULL);
		return ;
	}
	parse_and_create(fd, data);
}
