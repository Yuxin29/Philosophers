/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuwu <yuwu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:07:36 by yuwu              #+#    #+#             */
/*   Updated: 2025/09/07 14:22:56 by yuwu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// initiate all the int in the table
// if no argv5, then no defined minimal eating time, set it to -1
static void	init_table_ints(char **argv, t_table *table)
{
	table->nbr = safe_atoi(argv[1]);
	table->to_die_time = safe_atoi(argv[2]);
	table->eat_time = safe_atoi(argv[3]);
	table->sleep_time = safe_atoi(argv[4]);
	if (argv[5])
		table->total_eating_time = safe_atoi(argv[5]);
	else
		table->total_eating_time = -1;
	table->dead = 0;
	table->stop = 0;
	table->starting_time = now_ms();
}

// refill all the philos around the table
static void	init_philos(t_table *table)
{
	int		i;

	i = 1;
	while (i <= table->nbr)
	{
		table->philos[i].id = i;
		table->philos[i].fork_l = i;
		if (table->nbr == 1)
			table->philos[i].fork_r = -1;
		else if (i == table->nbr)
			table->philos[i].fork_r = 1;
		else
			table->philos[i].fork_r = i + 1;
		table->philos[i].meals_eaten = 0;
		table->philos[i].last_eating_time = table->starting_time;
		table->philos[i].table = table;
		i++;
	}
}

// initiate all the mutex and fork mutex
static void	init_mutex(t_table *table)
{
	int		i;

	i = 1;
	pthread_mutex_init(&table->printf_lock, NULL);
	pthread_mutex_init(&table->state_lock, NULL);
	while (i <= table->nbr)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	return ;
}

// pthread_create: create a new pthread
// SYNOPSIS  
// int pthread_create(pthread_t *thread,
//                     const pthread_attr_t *attr,
//                     void *(*start_routine)(void *),
//                     void *arg);
// param: id address, attribute, prt to a function, arg
// pthread_join: join with a terminated thread
// SYNOPSIS  
// int pthread_join(pthread_t thread, void **retval);
// pthread_create / pthread_join: return 0 success and 1 on eoor
//return 1 on suc and 0 on eoor
static int	create_and_join_threads(t_table *philo_table)
{
	pthread_t	monitor_thread;
	int			i;

	i = 1;
	while (i <= philo_table->nbr)
	{
		if (pthread_create(&philo_table->philos[i].thread, NULL,
				routine, &philo_table->philos[i]))
			return (0);
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, monitor, philo_table))
		return (0);
	i = 1;
	while (i <= philo_table->nbr)
	{
		if (pthread_join(philo_table->philos[i].thread, NULL))
			return (0);
		i++;
	}
	if (pthread_join(monitor_thread, NULL))
		return (0);
	return (1);
}

// argv prechecked befire this one 
// first malloc in this one
// in do all the initiate
// and create and join threads
t_table	*init_table(char **argv)
{
	t_table	*table;

	table = malloc(sizeof(t_table) * 1);
	if (!table)
		return (printf("%s\n", "Error: malloc table failed"), NULL);
	init_table_ints(argv, table);
	table->philos = malloc(sizeof(t_philo) * (table->nbr + 1));
	if (!table->philos)
		return (printf("%s\n", "Error: malloc inside table failed"), NULL);
	table->forks = malloc(sizeof(pthread_mutex_t) * (table->nbr + 1));
	if (!table->forks)
	{
		free(table->philos);
		printf("%s\n", "Error: malloc inside table failed");
		return (NULL);
	}
	init_philos(table);
	init_mutex(table);
	if (!create_and_join_threads(table))
		return (NULL);
	return (table);
}
