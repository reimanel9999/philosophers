/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manelcarvalho <manelcarvalho@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 13:38:03 by manu              #+#    #+#             */
/*   Updated: 2025/06/27 01:41:39 by manelcarval      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    t_table table;
    
    if (argc < 5 || argc > 6)
        error_msg("Number of arguments should be between 4 & 5, consider:");
    else
    {
        table_init(&table, argc, argv);
        if (!init_simulation(&table)) // && (table.meals_to_eat > 0 || table.meals_to_eat == -42)
		{
			cleanup(&table);
			error_msg("Dinner simulation error.");
		}
        cleanup(&table);
        return (EXIT_SUCCESS);
    }
    return (0);
}