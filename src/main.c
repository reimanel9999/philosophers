/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarvalh <mcarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 13:38:03 by manu              #+#    #+#             */
/*   Updated: 2025/06/17 12:07:00 by mcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    t_table table;
    
    if (argc == 5 || argc == 6)
    {
        
        table_init(&table, argc, argv);
		// printf("Thread init: %lu\n", table.philos[3].thread);
        if (init_simulation(&table))
			error_msg("Dinner simulation error.");
        // end_simulation(&table);
        return (EXIT_SUCCESS);
    }
    else
        error_msg("Number of arguments should be between 4 & 5, consider:");
    return (0);
}