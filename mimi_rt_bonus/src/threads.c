/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 05:25:32 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/21 00:42:46 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mini_rt_bonus.h"
# include <pthread.h>

t_renderer	*init_threads(t_app *app)
{
	int			i;
	t_renderer	*threads;

	i = 0;
	threads = ft_calloc(sizeof(t_renderer), THREADS_NB);
	if (!threads)
		return (NULL);
	while (i < THREADS_NB)
	{
		threads[i].id = i;
		threads[i].app = app;
		i++;
	}
	return (threads);
}

void	launch_threads(t_renderer *threads)
{
	int	i;

	i = 0;
	while (i < THREADS_NB)
	{
		if (pthread_create(&threads[i].tid, NULL, draw_scene_routine,
				(void *)&threads[i]))
			write(STDERR_FILENO, "pthread_create() failed\n", 24);
		i++;
	}
}

void	join_threads(t_renderer *threads)
{
	int	i;

	i = 0;
	while (i < THREADS_NB)
	{
		if (pthread_join(threads[i].tid, NULL))
			write(STDERR_FILENO, "pthread_join() failed\n", 22);
		i++;
	}
}
