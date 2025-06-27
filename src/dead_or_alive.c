/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_or_alive.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manelcarvalho <manelcarvalho@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:51:19 by manelcarval       #+#    #+#             */
/*   Updated: 2025/06/27 01:20:42 by manelcarval      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	death_of_philo(t_table *table)
{
	int		i;
	long	current_time;

	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_mutex_lock(&table->philos[i].philo_mutex);
		current_time = real_time(0); // Get current time in milliseconds
		if (current_time - table->philos[i].last_meal > table->time_to_die)
		{
			pthread_mutex_lock(&table->write_mtx);
			printf("%ld %d died\n", current_time - table->sim_start, table->philos[i].id);
			pthread_mutex_unlock(&table->write_mtx);
			pthread_mutex_unlock(&table->philos[i].philo_mutex);
			table->sim_stop = true;
			return (true);
		}
		pthread_mutex_unlock(&table->philos[i].philo_mutex);
		i++;
	}
	return (false);
}

static bool	all_philos_full(t_table *table)
{
	int	i;

	if (table->meals_to_eat == -42)
		return (false);
	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_mutex_lock(&table->philos[i].philo_mutex);
		if (table->philos[i].meals_nbr < table->meals_to_eat)
		{
			pthread_mutex_unlock(&table->philos[i].philo_mutex);
			return (false);
		}
		pthread_mutex_unlock(&table->philos[i].philo_mutex);
		i++;
	}
	return (true);
}

void	*shikigami(void *temp)
{
	t_table	*table;

	table = (t_table *)temp;
	// Wait for all philosopher threads to be running and ready
	while (1)
	{
		pthread_mutex_lock(&table->table_mtx);
		if (table->running_threads == table->philo_nbr)
		{
			pthread_mutex_unlock(&table->table_mtx);
			break;
		}
		pthread_mutex_unlock(&table->table_mtx);
		usleep(100);
	}
	while (!table->sim_stop)
	{
		if (death_of_philo(table))
			return (NULL);
		if (all_philos_full(table))
		{
			pthread_mutex_lock(&table->table_mtx);
			table->sim_stop = true;
			pthread_mutex_unlock(&table->table_mtx);
			return (NULL);
		}
		precise_usleep(5, table); // Check every 5ms to reduce race conditions
	}
	return (NULL);
}
