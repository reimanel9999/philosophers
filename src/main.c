/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarvalh <mcarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 13:38:03 by manu              #+#    #+#             */
/*   Updated: 2025/06/25 15:58:29 by mcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    t_table table;
    
    if (argc == 5 || argc == 6)
    {
        table_init(&table, argc, argv);
		printf("Inputs: philos - %d; die - %ld; eat - %ld; sleep - %ld\n", table.philo_nbr, table.time_to_die, table.time_to_eat, table.time_to_sleep);
        if (!init_simulation(&table)) // && (table.meals_to_eat > 0 || table.meals_to_eat == -42)
		{
			cleanup(&table);
			error_msg("Dinner simulation error.");
		}
        cleanup(&table);
        return (EXIT_SUCCESS);
    }
    else
        error_msg("Number of arguments should be between 4 & 5, consider:");
    return (0);
}