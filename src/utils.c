/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarvalh <mcarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:07:05 by manelcarval       #+#    #+#             */
/*   Updated: 2025/06/25 15:22:41 by mcarvalh         ###   ########.fr       */
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
	
	if (gettimeofday(&tv, NULL))
		error_msg("Time of day error");
	if (micro_converter == micro)
		return ((tv.tv_sec * 1000 * micro) + tv.tv_usec);
	else
		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));

}

void	precise_usleep(long usec)
{
	long	start;
	long	current;

	start = real_time(micro); // convert ms to us
	while (1)
	{
		current = real_time(micro); // convert ms to us
		if (current - start >= usec)
			break ;
		usleep(100); // sleep in small chunks
	}
}
