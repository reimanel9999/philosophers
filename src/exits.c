/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarvalh <mcarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 21:52:23 by manelcarval       #+#    #+#             */
/*   Updated: 2025/06/17 12:53:50 by mcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	man_error(char *error)
{
	printf("%s\n", error);
	return (1);
}

void	error_msg(char *error)
{
	printf("%s\n%s\n", error, USAGE);
	exit(EXIT_FAILURE);
}