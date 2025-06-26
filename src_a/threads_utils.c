/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manelcarvalho <manelcarvalho@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:33:21 by mcarvalh          #+#    #+#             */
/*   Updated: 2025/06/26 23:56:18 by manelcarval      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sync_threads(t_table *table)
{
	while (1)
	{
		pthread_mutex_lock(&table->table_mtx);
		if (table->all_threads == true)
		{
			pthread_mutex_unlock(&table->table_mtx);
			break;
		}
		pthread_mutex_unlock(&table->table_mtx);
		usleep(100);
	}
}

void	threads_ready(long sim_start)
{
	while (real_time(0) < sim_start)
		usleep(100);
}

// Apagar!!

static int	handel_thread(int status, t_thread_status opcode)
{
	if (status == 0)
		return (0);
	if (EINVAL == status && (LOCK == opcode || UNLOCK == opcode))
		return (man_error( "The value is invalid" ));
	else if (EINVAL == status && INIT == opcode)
		return (man_error( "The value is invalid" ));
	else if (EDEADLK == status)
		return (man_error("A deadlock would occur"));
	else if (EPERM == status)
		return (man_error("The tread does not hold a lock on mutex"));
	else if (ENOMEM == status)
		return (man_error( "Not enough memory to create another mutex"));
	else if (EBUSY == status)
		return (man_error("Mutex is locked"));
	return (status);
}

int	man_thread(pthread_t *thread, void *(*function)(void *), void *temp, t_thread_status code)
{
	if (code == CREATE)
	{
		return (handel_thread(pthread_create(thread, NULL, function, temp), code));
	}
	else if (code == JOIN)
	{
		return (handel_thread(pthread_join(*thread, NULL), code));
	}
	else
		return (man_error("Wrong thread operation"));
	return (0);
}