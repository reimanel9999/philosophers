/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manelcarvalho <manelcarvalho@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 01:43:00 by manelcarval       #+#    #+#             */
/*   Updated: 2025/06/27 01:43:34 by manelcarval      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	// Add a small delay to prevent immediate grabbing of both forks
	if (philo->id % 2 == 0)
		precise_usleep(1, philo->table);
	
	// Pick up forks in the order assigned during initialization
	pthread_mutex_lock(&philo->fork_one->fork);
	print_status(philo, FIRST_FORK);
	
	pthread_mutex_lock(&philo->fork_two->fork);
	print_status(philo, SECOND_FORK);
	
	pthread_mutex_lock(&philo->philo_mutex);
	philo->last_meal = real_time(0); // Get current time in milliseconds
	philo->meals_nbr++;
	print_status(philo, EATING);
	pthread_mutex_unlock(&philo->philo_mutex);
	
	precise_usleep(philo->table->time_to_eat, philo->table);
	
	// Release forks in reverse order
	pthread_mutex_unlock(&philo->fork_two->fork);
	pthread_mutex_unlock(&philo->fork_one->fork);
}

void	sleeping(t_philo *philo)
{
	print_status(philo, SLEEPING);
	precise_usleep(philo->table->time_to_sleep, philo->table);
}

void	contemplating(t_philo *philo)
{
	long	time_to_think;
	long	elapsed;

	print_status(philo, CONTEMPLATING);
	pthread_mutex_lock(&philo->philo_mutex);
	elapsed = real_time(0) - philo->last_meal;
	pthread_mutex_unlock(&philo->philo_mutex);
	time_to_think = (philo->table->time_to_die - elapsed - philo->table->time_to_eat) / 2;
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	precise_usleep(time_to_think, philo->table);
}
