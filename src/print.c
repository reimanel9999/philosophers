/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manelcarvalho <manelcarvalho@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:05:40 by mcarvalh          #+#    #+#             */
/*   Updated: 2025/06/26 23:42:49 by manelcarval      ###   ########.fr       */
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
	curr_time = real_time(0) - philo->table->sim_start;
	if (status == CONTEMPLATING)
		printf("%ld %d is thinking\n", curr_time, philo->id);
	else if (status == DIED)
		printf("%ld %d died\n", curr_time, philo->id);
	else if (status == EATING)
		printf("%ld %d is eating\n", curr_time, philo->id);
	else if (status == SLEEPING)
		printf("%ld %d is sleeping\n", curr_time, philo->id);
	else if (status == FIRST_FORK || status == SECOND_FORK)
		printf("%ld %d has taken a fork\n", curr_time, philo->id);
	pthread_mutex_unlock(&philo->table->write_mtx);
}
