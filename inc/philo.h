/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarvalh <mcarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 13:39:02 by manu              #+#    #+#             */
/*   Updated: 2025/06/17 17:47:20 by mcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <stdbool.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>

# define USAGE	"Usage: ./philo <number_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
[number_of_times_each_philosopher_must_eat]"

# define mili (double) 1000.00 // miliseconds converter

typedef struct s_philo t_philo;

typedef enum e_thread_status
{
	CREATE,
	JOIN,
	INIT,
	LOCK,
	UNLOCK,
	DESTROY	
}	t_thread_status;

typedef enum e_status
{
	EATING,
	SLEEPING,
	CONTEMPLATING,
	FIRST_FORK,
	SECOND_FORK,
	DIED,
}	t_status;

typedef struct s_fork
{
    int				fork_id;
    pthread_mutex_t	fork;
} t_fork;

typedef struct s_table
{
    long            philo_nbr;
    long            time_to_die;
    long            time_to_eat;
    long            time_to_sleep;
    long            meals_to_eat;
    long            start_sim;
    bool            stop_sim;
    pthread_t       monitor;
    pthread_mutex_t write_mtx;
    pthread_mutex_t table_mtx;
    t_fork  		*fork;
    t_philo         *philos;
} t_table;

typedef struct s_philo
{    	
    pthread_t       	thread;
    int		        	id;
    long		        meals_nbr;
    // int			is_valid;
    long		        last_meal;
    // int            		full;
    t_fork              *fork_one;
    t_fork              *fork_two;
    pthread_mutex_t		philo_mutex;
    t_table             *table;
} t_philo;

//data_init.c

void	table_init(t_table *table, int argc, char **argv);

//utils.c

bool	ft_isdigit(char *str);
int		ft_atoi(const char *str);

//exits.c

void	error_msg(char *error);

#endif