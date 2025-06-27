/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manelcarvalho <manelcarvalho@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 13:39:02 by manu              #+#    #+#             */
/*   Updated: 2025/06/27 02:25:31 by manelcarval      ###   ########.fr       */
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

# define micro (double) 1000.00 // microseconds converter

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
	CONTEMPLATING,
	DIED,
	EATING,
	SLEEPING,
	FIRST_FORK,
	SECOND_FORK,
}	t_status;

typedef struct s_fork
{
    int				fork_id;
    pthread_mutex_t	fork;
} t_fork;

typedef struct s_table
{
    int				philo_nbr;
    long            time_to_die;
    long            time_to_eat;
    long            time_to_sleep;
    long            meals_to_eat;
    long            sim_start;
	bool			all_threads;
    bool            sim_stop;
    long            running_threads;
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
    // int            		stuffed;
    t_fork              *fork_one;
    t_fork              *fork_two;
    pthread_mutex_t		philo_mutex;
    t_table             *table;
} t_philo;

//data_init.c

void	table_init(t_table *table, int argc, char **argv);

//simulation.c

bool	init_simulation(t_table *table);
void	*dinner_start(void *temp);

// routines.c

void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	contemplating(t_philo *philo);

//threads_utils.c

void    man_thread(pthread_t *thread, void *(*function)(void *), void *temp, t_thread_status code);
void	sync_threads(t_table *table);
void	threads_ready(long time);

// dead_or_alive

void	*shikigami(void *temp);

// print.c

void	print_status(t_philo *philo, t_status status);

//utils.c

bool	dinner_end(t_table *table);
bool	ft_isdigit(char *str);
int		ft_atoi(const char *str);
long	real_time(long micro_converter);
void	precise_usleep(long msec, t_table *table);

//exits.c

void	cleanup(t_table *table);
void	error_msg(char *error);
int     man_error(char *error);

#endif