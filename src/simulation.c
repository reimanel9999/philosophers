/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manelcarvalho <manelcarvalho@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 01:16:00 by mcarvalh          #+#    #+#             */
/*   Updated: 2025/06/27 02:29:55 by manelcarval      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*introvert(void *temp)
{
	t_philo	*philo;
	long	start_time;
	long	time_to_wait;

	philo = (t_philo *)temp;
	start_time = real_time(0);
	pthread_mutex_lock(&philo->fork_one->fork);
	print_status(philo, FIRST_FORK);
	time_to_wait = philo->table->time_to_die - (real_time(0) - start_time);
	precise_usleep(time_to_wait, philo->table);
	print_status(philo, DIED);
	pthread_mutex_unlock(&philo->fork_one->fork);
	return (NULL);
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
		if (dinner_end(philo->table))
			break ;
		sleeping(philo);
		if (dinner_end(philo->table))
			break ;
		contemplating(philo);
	}
	// Small delay to ensure proper cleanup
	usleep(1000);
	return (NULL);
}

bool	init_simulation(t_table *table)
{
	int	m;

	m = -1;
	if (table->philo_nbr == 1)
	{
		table->sim_start = real_time(0); // Start immediately for single philosopher
		man_thread(&table->philos[0].thread, &introvert, &table->philos[0], CREATE);
		man_thread(&table->philos[0].thread, NULL, NULL, JOIN);
		return (true);
	}
	else
	{
		table->sim_start = real_time(0) + (table->philo_nbr * 42); // Future start time
		while (++m < table->philo_nbr)
			man_thread(&table->philos[m].thread, &dinner_start, &table->philos[m], CREATE);
	}
	man_thread(&table->monitor, &shikigami, table, CREATE);
	pthread_mutex_lock(&table->table_mtx);
	table->all_threads = true;
	pthread_mutex_unlock(&table->table_mtx);
	m = -1;
	while (++m < table->philo_nbr)
		man_thread(&table->philos[m].thread, NULL, NULL, JOIN);
	man_thread(&table->monitor, NULL, NULL, JOIN);
	return (true);
}
