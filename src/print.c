/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarvalh <mcarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:05:40 by mcarvalh          #+#    #+#             */
/*   Updated: 2025/06/25 15:53:58 by mcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, t_status status)
{
	long	curr_time;
	// long	now;

	if (dinner_end(philo->table))
		return ;
	pthread_mutex_lock(&philo->table->write_mtx);
	// now = real_time(true); // apagar
	curr_time = real_time(true) - philo->table->sim_start;
	// printf("%ld %d %s (debug: now=%ld, start=%ld)\n", curr_time, philo->id, status, now, philo->table->sim_start); // apagar
	if (status == CONTEMPLATING)
		printf("%ld philo: %d is contemplating...", curr_time, philo->id);	
	else if (status == DIED)
		printf("%ld philo: %d has died!", curr_time, philo->id);	
	else if (status == EATING)
		printf("%ld philo: %d is eating", curr_time, philo->id);	
	else if (status == SLEEPING)
		printf("%ld philo: %d is sleeping", curr_time, philo->id);
	else if (status == FIRST_FORK || status == SECOND_FORK)
		printf("%ld philo: %d has picked up a fork", curr_time, philo->id);
	pthread_mutex_unlock(&philo->table->write_mtx);
}
