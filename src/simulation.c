/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarvalh <mcarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 01:16:00 by mcarvalh          #+#    #+#             */
/*   Updated: 2025/06/25 16:49:49 by mcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eating(t_philo *philo)
{
	// Add a small delay to prevent immediate grabbing of both forks
	if (philo->id % 2 == 0)
		precise_usleep(100);
	
	// Pick up forks in the order assigned during initialization
	pthread_mutex_lock(&philo->fork_one->fork);
	print_status(philo, FIRST_FORK);
	
	pthread_mutex_lock(&philo->fork_two->fork);
	print_status(philo, SECOND_FORK);
	
	pthread_mutex_lock(&philo->philo_mutex);
	philo->last_meal = real_time(true);
	philo->meals_nbr++;
	print_status(philo, EATING);
	pthread_mutex_unlock(&philo->philo_mutex);
	
	precise_usleep(philo->table->time_to_eat * 100);
	
	// Release forks in reverse order
	pthread_mutex_unlock(&philo->fork_two->fork);
	pthread_mutex_unlock(&philo->fork_one->fork);
}

static void	sleeping(t_philo *philo)
{
	print_status(philo, SLEEPING);
	precise_usleep(philo->table->time_to_sleep * 100);
}

static void	contemplating(t_philo *philo)
{
	print_status(philo, CONTEMPLATING);
	// Small delay to prevent immediate fork grabbing
	precise_usleep(100);
}

void	*dinner_start(void *temp)
{
	t_philo	*philo;

	philo = (t_philo *)temp;
	sync_threads(philo->table->all_threads);	
	// Set initial last_meal time to current time
	pthread_mutex_lock(&philo->philo_mutex);
	philo->last_meal = real_time(true);
	pthread_mutex_unlock(&philo->philo_mutex);
	threads_ready(philo->table->sim_start);
	printf("TIME: %ld", philo->table->sim_start);
	while (!dinner_end(philo->table))
	{
		eating(philo);
		if (philo->table->sim_stop)
			break ;
		sleeping(philo);
		if (philo->table->sim_stop)
			break ;
		contemplating(philo);
	}
	return (NULL);
}

bool	init_simulation(t_table *table)
{
	int	m;

	m = -1;
	table->sim_start = real_time(true) + (table->philo_nbr * 100); // Increased offset for proper timing
	if (table->philo_nbr == 1)
	{
		if (man_thread(&table->philos[0].thread, &dinner_start, &table->philos[0], CREATE))
			return (man_error("Error: Failed to create thread for philosopher 1\n"));
	}
	else
	{
		while (++m < table->philo_nbr)
		{
			if (man_thread(&table->philos[m].thread, &dinner_start, &table->philos[m], CREATE))
			{
				// return (man_error("Error: Failed to create thread for philosophers\n"));
				printf("Error: Failed to create thread for philosopher %d\n", m + 1);
				return (false);
			}
		}
	}
	if (man_thread(&table->monitor, &shikigami, table, CREATE))
	{
		// return (man_error("Error: Failed to create monitor thread\n"));
		printf("Error: Failed to create monitor thread\n");
		return (false);
	}
	pthread_mutex_lock(&table->table_mtx);
	table->all_threads = true;
	pthread_mutex_unlock(&table->table_mtx);
	// Join all threads
	m = -1;
	while (++m < table->philo_nbr)
		man_thread(&table->philos[m].thread, NULL, NULL, JOIN);
	pthread_mutex_lock(&table->table_mtx);
	table->sim_stop = true;
	pthread_mutex_unlock(&table->table_mtx);
	man_thread(&table->monitor, NULL, NULL, JOIN);
	return (true);
}
