/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarvalh <mcarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:33:21 by mcarvalh          #+#    #+#             */
/*   Updated: 2025/06/25 13:43:14 by mcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sync_threads(bool finished_threads)
{
	while (finished_threads == false)
		continue ;
}

void	threads_ready(long sim_start)
{
	while (real_time(1) < sim_start)
		continue ;	
}

int	man_thread(pthread_t *thread, void *(*function)(void *), void *temp, t_thread_status code)
{
	if (code == CREATE)
	{
		if (pthread_create(thread, NULL, function, temp) != 0)
			return(man_error("Failed to create thread!"));
	}
	else if (code == JOIN)
	{
		if (pthread_join(*thread, NULL) != 0)
			return (man_error("Failed to join thread!"));
	}
	else
		return (man_error("Wrong thread operation"));
	return (0);
}