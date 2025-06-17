/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarvalh <mcarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 01:16:00 by mcarvalh          #+#    #+#             */
/*   Updated: 2025/06/17 12:54:53 by mcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	dinner_start(void *temp)
{
	t_philo	*philo;

	philo = (t_philo *)temp;
}

bool	init_simulation(t_table *table)
{
	int	m;

	m = -1;
	if (table->philo_nbr == 1)
	{
			if (pthread_create(&table->philos[m].thread, NULL,
			&dinner_start, &table->philos[m] != 0))
				return (man_error("Incomplete thread creation."));
	}
	else
	{
		while (++m < table->philo_nbr)
		{
			if (pthread_create(&table->philos[m].thread, NULL,
			&dinner_start, &table->philos[m] != 0))
				return (man_error("Incomplete thread creation."));
		}
	}
	




	return (true);
}
