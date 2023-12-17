/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_bonus.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:55:08 by srapin            #+#    #+#             */
/*   Updated: 2023/12/17 06:18:53 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_BONUS_H
# define STRUCT_BONUS_H

# include <pthread.h>
# include "struct.h"

typedef struct s_renderer
{
	pthread_t			tid;
	int					id;
	t_app				*app;
}						t_renderer;

#endif