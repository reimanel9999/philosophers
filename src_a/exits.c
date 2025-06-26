/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarvalh <mcarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 21:52:23 by manelcarval       #+#    #+#             */
/*   Updated: 2025/06/25 09:42:53 by mcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_mutex_destroy(&table->philos[i].philo_mutex);
		pthread_mutex_destroy(&table->fork[i].fork);
		i++;
	}
	pthread_mutex_destroy(&table->table_mtx);
	pthread_mutex_destroy(&table->write_mtx);
	free(table->philos);
	free(table->fork);
}

int	man_error(char *error)
{
	printf("%s\n%s\n", error, USAGE);
	return (false);
}

void	error_msg(char *error)
{
	printf("%s\n%s\n", error, USAGE);
	exit(EXIT_FAILURE);
}