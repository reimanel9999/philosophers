/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manelcarvalho <manelcarvalho@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:07:05 by manelcarval       #+#    #+#             */
/*   Updated: 2025/06/16 03:36:24 by manelcarval      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_isdigit(char	*str)
{
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			return (0);
		str++;
	}
	return (1);
}

void	check_input(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str++))
			error_msg("Input is not a digit\n");	
	}
}

int	ft_atoi(const char *str)
{
	int		sign;
	long	number;

	number = 0;
	while (*str && (*str == ' ' || (*str >= 9 && *str <= 13) || *str == '+'))
		str++;
	if (!ft_isdigit(*str))
		error_msg("Input has non-digit characters\nPlease use only digits");
	check_input(*str);
	while (*str >= '0' && *str <= '9')
	{
		number = number * 10 + sign * (*str++ - '0');
		if (number > INT_MAX)
			error_msg("Value is bigger than INT_MAX (2,147,483,647)");
		else if (number < INT_MIN)
			error_msg("Value is smaller than INT_MIN (-2,147,483,648)");
	}
	return ((int)number);
}
