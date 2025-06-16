/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manelcarvalho <manelcarvalho@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 21:52:23 by manelcarval       #+#    #+#             */
/*   Updated: 2025/06/12 18:13:27 by manelcarval      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_msg(char *error)
{
	printf("%s\n%s\n", error, USAGE);
	exit(EXIT_FAILURE);
}