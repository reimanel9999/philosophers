/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarvalh <mcarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:33:21 by mcarvalh          #+#    #+#             */
/*   Updated: 2025/06/17 17:45:42 by mcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	man_mutex(pthread_mutex_t *mtx, t_thread_status code)
{
	if (code == INIT)
		pthread_mutex_init(mtx, NULL);
	else if (code == LOCK)
		pthread_mutex_lock(mtx);
	else if (code == UNLOCK)
		pthread_mutex_unlock(mtx);
	else if (code == DESTROY)
		pthread_mutex_destroy(mtx);
}

void	man_thread(pthread_t *thread, void *(*function)(void *), void)
{
	
}