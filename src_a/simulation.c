/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manelcarvalho <manelcarvalho@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 01:16:00 by mcarvalh          #+#    #+#             */
/*   Updated: 2025/06/27 01:10:40 by manelcarval      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eating(t_philo *philo)
{
	// Add a small delay to prevent immediate grabbing of both forks
	if (philo->id % 2 == 0)
		precise_usleep(100, philo->table);
	
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

static void	sleeping(t_philo *philo)
{
	print_status(philo, SLEEPING);
	precise_usleep(philo->table->time_to_sleep, philo->table);
}

static void	contemplating(t_philo *philo)
{
	long	time_to_think;
	long	elapsed;

	print_status(philo, CONTEMPLATING);
	pthread_mutex_lock(&philo->philo_mutex);
	elapsed = real_time(0) - philo->last_meal;
	pthread_mutex_unlock(&philo->philo_mutex);
	time_to_think = (philo->table->time_to_die - elapsed - philo->table->time_to_eat) / 4;
	if (time_to_think < 0 || time_to_think > 50)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	precise_usleep(time_to_think, philo->table);
}

void	*dinner_start(void *temp)
{
	t_philo	*philo;

	philo = (t_philo *)temp;
	// Wait for all threads to be created
	sync_threads(philo->table);
	// Set last_meal to simulation start time
	pthread_mutex_lock(&philo->philo_mutex);
	philo->last_meal = philo->table->sim_start;
	pthread_mutex_unlock(&philo->philo_mutex);
	// Increment running_threads counter
	pthread_mutex_lock(&philo->table->table_mtx);
	philo->table->running_threads++;
	pthread_mutex_unlock(&philo->table->table_mtx);
	// Wait for simulation to start
	threads_ready(philo->table->sim_start);
	// Odd philosophers start with thinking to avoid deadlock (like mcombeau)
	if (philo->id % 2 == 1)
		contemplating(philo);
	while (!dinner_end(philo->table))
	{
		eating(philo);
		// Check if this philosopher has finished their meals
		pthread_mutex_lock(&philo->philo_mutex);
		if (philo->table->meals_to_eat != -42 && philo->meals_nbr >= philo->table->meals_to_eat)
		{
			pthread_mutex_unlock(&philo->philo_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->philo_mutex);
		if (philo->table->sim_stop)
			break ;
		sleeping(philo);
		if (philo->table->sim_stop)
			break ;
		contemplating(philo);
		if (philo->table->sim_stop)
			break ;
	}
	// Small delay to ensure proper cleanup
	usleep(1000);
	return (NULL);
}

bool	init_simulation(t_table *table)
{
	int	m;

	m = -1;
	table->sim_start = real_time(0) + (table->philo_nbr * 2 * 10); // Future start time
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
	// Set stop flag and join monitor
	pthread_mutex_lock(&table->table_mtx);
	table->sim_stop = true;
	pthread_mutex_unlock(&table->table_mtx);
	man_thread(&table->monitor, NULL, NULL, JOIN);
	return (true);
}
