/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarvalh <mcarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:07:05 by manelcarval       #+#    #+#             */
/*   Updated: 2025/06/17 11:21:38 by mcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
