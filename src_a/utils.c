/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manelcarvalho <manelcarvalho@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:07:05 by manelcarval       #+#    #+#             */
/*   Updated: 2025/06/27 00:17:00 by manelcarval      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	dinner_end(t_table *table)
{
	bool	temp;

	temp = false;
	pthread_mutex_lock(&table->table_mtx);
	if (table->sim_stop == true)
		temp = true;
	pthread_mutex_unlock(&table->table_mtx);
	return (temp);
}

bool	ft_isdigit(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (false);
		// printf("Is a digit: %s\n", str);
		str++;
	}
	return (true);
}

int	ft_atoi(const char *str)
{
	int		m;
	long	number;

	m = 0;
	number = 0;
	while (str[m] >= '0' && str[m] <= '9')
	{
		number = number * 10 + (str[m] - '0');
		if (number > INT_MAX)
			error_msg("Value is bigger than INT_MAX (2,147,483,647)");
		else if (number < INT_MIN)
			error_msg("Value is smaller than INT_MIN (-2,147,483,648)");
		m++;
	}
	// printf("ft_atoi: %d\n", (int)number);
	return ((int)number);
}

long	real_time(long micro_converter)
{
	struct timeval	tv;

	(void)micro_converter; // Suppress unused parameter warning
	if (gettimeofday(&tv, NULL))
		error_msg("Time of day error");
	// Always return milliseconds for consistency
	// tv.tv_sec is in seconds, tv.tv_usec is in microseconds
	// Convert: seconds * 1000 + microseconds / 1000 = milliseconds
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	precise_usleep(long msec, t_table *table)
{
	long start;
	long elapsed;
	long rem;

	start = real_time(0); // Get start time in milliseconds
	while (real_time(0) - start < msec)
	{
		if (dinner_end(table))
			break;
		elapsed = real_time(0) - start;
		rem = msec - elapsed;
		if (rem > 1)
			usleep((rem * 1000) / 2); // Convert to microseconds for usleep
		else
		{
			while (real_time(0) - start < msec)
				;
		}
	}
}
