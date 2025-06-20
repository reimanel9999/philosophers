/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manelcarvalho <manelcarvalho@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 13:38:03 by manu              #+#    #+#             */
/*   Updated: 2025/06/16 03:37:31 by manelcarval      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    t_table table;
    
    if (argc == 5 || argc == 6)
    {
        
        table_init(&table, argv);
        init_simulation(&table);
        end_simulation(&table);
        return (EXIT_SUCCESS);
    }
    else
        error_msg("Number of arguments should be between 4 & 5, consider:");
    return (0);
}