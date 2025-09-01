/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuwu <yuwu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:07:36 by yuwu              #+#    #+#             */
/*   Updated: 2025/09/01 18:09:09 by yuwu             ###   ########.fr       */
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
	table->starting_time_ms = now_ms();
}

// refill all the philos around the table
static void	init_philos(t_table *table)
{
	int		i;

	i = 0;
	while (i < table->nbr - 1)
	{
		table->philos[i].id = i;
		table->philos[i].fork_l = i;
		table->philos[i].fork_r = i + 1;
		table->philos[i].meals_eaten = 0;
		table->philos[i].last_eating_time = table->starting_time_ms;
		table->philos[i].table = table;
		i++;
	}
	table->philos[i].id = i;
	table->philos[i].fork_l = i;
	table->philos[i].fork_r = 0;
	table->philos[i].meals_eaten = 0;
	table->philos[i].last_eating_time = table->starting_time_ms;
	table->philos[i].table = table;
}

// initiate all the mutex and fork mutex
static void	init_mutex(t_table *table)
{
	int		i;

	i = 0;
	pthread_mutex_init(&table->printf_lock, NULL);
	pthread_mutex_init(&table->state_lock, NULL);
	while (i < table->nbr)
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
static void	create_and_join_threads(t_table *philo_table)
{
	pthread_t	monitor_thread;
	int			i;

	i = 0;
	while (i < philo_table->nbr)
	{
		pthread_create(&philo_table->philos[i].thread, NULL, routine, &philo_table->philos[i]);
		i++;
	}
	pthread_create(&monitor_thread, NULL, monitor, philo_table);
	i = 0;
	while (i < philo_table->nbr)
	{
		pthread_join(philo_table->philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
	return ;
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
	{
		printf("%s\n", "malloc table failed");
		return (NULL);
	}
	table->philos = malloc(sizeof(t_philo) * table->nbr);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->nbr);
	if (!table->philos || !table->forks)
	{
		ft_free_table(table);
		printf("%s\n", "malloc inside table failed");
		return (NULL);
	}
	init_table_ints(argv, table);
	init_philos(table);
	init_mutex(table);
	create_and_join_threads(table);
	return (table);
}
