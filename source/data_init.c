/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manelcarvalho <manelcarvalho@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 19:17:46 by manelcarval       #+#    #+#             */
/*   Updated: 2025/06/16 05:12:51 by manelcarval      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	fork_init(t_philo *philos, t_fork *fork, int pos)
{
	int	philo_nbr;

	philo_nbr = philos->table->philo_nbr;
	philos->fork_one = &fork[pos];
	philos->fork_two = &fork[(pos + 1) % philo_nbr];
	if (philos->id % 2 != 0)
	{
		philos->fork_two = &fork[pos];
		philos->fork_one = &fork[(pos + 1) % philo_nbr];
	}
}

static void	philo_init(t_table *table)
{
	t_philo	*philos;
	int		m;

	m = 0;
	while (m < table->philo_nbr)
	{
		philos = &table->philos[m];
		philos->id = m + 1;
		philos->meals_nbr = 0;
		philos->last_meal = 0;
		if (pthread_mutex_init(&philos->philo_mutex, NULL) != 0)
		{
			//apagar depois
			printf("Failed to initialize mutex for philosopher %d\n", philos->id);
			error_msg("Philo mutex initialization failed.");
		}
		fork_init(philos, table->fork, m);
		m++;
	}
	
}

static void	threads_init(t_table *table)
{
	int	m;

	m = 0;
	table->start_sim = false;
	table->stop_sim = false;
	table->philos = malloc(sizeof(t_philo *) * table->philo_nbr);
	if (!table->philos)
		error_msg("Philosophers memory allocation failed.");
	table->fork = malloc(sizeof(t_fork) * table->philo_nbr);
	if (!table->fork)
		error_msg("Fork memory allocation failed.");
	while (m < table->philo_nbr)
	{
		if (pthread_mutex_init(&table->fork[m].fork, NULL) != 0)		
			error_msg("Fork mutex initialization failed.");
		table->fork[m].fork_id = m;
		m++;
	}
	if (pthread_mutex_init(&table->table_mtx, NULL) != 0)
		error_msg("Table mutex initialization failed.");
	if (pthread_mutex_init(&table->write_mtx, NULL) != 0)
		error_msg("Write mutex initialization failed.");
}

void	table_init(t_table *table, char **argv)
{
	table->philo_nbr = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]) * mili;
	table->time_to_eat = ft_atoi(argv[3]) * mili;
	table->time_to_die = ft_atoi(argv[4]) * mili;
	if (argv[5])
	{
		table->meals_to_eat = ft_atoi(argv[5]);
		if (table->meals_to_eat <= 0)
			error_msg("Number of meals for each philo has to bigger than 0.");
	}
	else
		table->meals_to_eat = -1;
	if (table->philo_nbr <= 60 * mili || table->time_to_die <= 60 * mili \
	|| table->time_to_die <= 60 * mili || table->time_to_sleep <= 60 * mili)
		error_msg("Timestamp has to be bigger than 60ms.");
	threads_init(table);
	philo_init(table);
}
