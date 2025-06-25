/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarvalh <mcarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 19:17:46 by manelcarval       #+#    #+#             */
/*   Updated: 2025/06/25 11:27:13 by mcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	valid_input(int argc, char **argv)
{
	int	m;
	// int	nbr;

	m = 1;
	while (m < argc)
	{
		if(!ft_isdigit(argv[m]))
			return (false);
		// nbr = ft_atoi(argv[m]);
		m++;
	}
	return (true);
}

static void	fork_init(t_philo *philos, t_fork *fork, int pos)
{
	int	philo_nbr;

	philo_nbr = philos->table->philo_nbr;
	
	// Deadlock prevention strategy:
	// Even philosophers: pick up left fork first, then right
	// Odd philosophers: pick up right fork first, then left
	// This breaks the circular wait condition
	
	if (philos->id % 2 == 0)
	{
		// Even philosophers: left fork first, then right
		philos->fork_one = &fork[pos];                    // Left fork
		philos->fork_two = &fork[(pos + 1) % philo_nbr];  // Right fork
	}
	else
	{
		// Odd philosophers: right fork first, then left
		philos->fork_one = &fork[(pos + 1) % philo_nbr];  // Right fork
		philos->fork_two = &fork[pos];                    // Left fork
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
		philos->table = table;
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
	table->sim_start = false;
	table->sim_stop = false;
	table->all_threads = false;
	table->philos = malloc(sizeof(t_philo) * table->philo_nbr);
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

void	table_init(t_table *table, int argc, char **argv)
{
	if (!valid_input(argc, argv))
		error_msg("Invalid Input.\n Please use only positive integers.");
	table->philo_nbr = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]) * micro;
	table->time_to_eat = ft_atoi(argv[3]) * micro;
	table->time_to_sleep = ft_atoi(argv[4]) * micro;
	if (argv[5])
	{
		table->meals_to_eat = ft_atoi(argv[5]);
		if (table->meals_to_eat <= 0)
			error_msg("Number of meals for each philo has to bigger than 0.");
	}
	else
		table->meals_to_eat = -42;
	if (table->time_to_die <= 60 * micro \
	|| table->time_to_eat <= 60 * micro || table->time_to_sleep <= 60 * micro)
		error_msg("Timestamp has to be bigger than 60ms.");
	printf("Init Threads!\n");
	threads_init(table);
	philo_init(table);
}
