/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuwu <yuwu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:07:54 by yuwu              #+#    #+#             */
/*   Updated: 2025/09/07 16:29:19 by yuwu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// free the table and philos, and destroy all the mutex
void	ft_free_table(t_table *table)
{
	int	i;

	i = 1;
	if (!table)
		return ;
	if (table->philos)
		free(table->philos);
	if (table->forks)
	{
		while (i <= table->nbr)
		{
			pthread_mutex_destroy(&table->forks[i]);
			i++;
		}
		free(table->forks);
	}
	pthread_mutex_destroy(&table->printf_lock);
	pthread_mutex_destroy(&table->state_lock);
	free (table);
	return ;
}

// check if all philo has eateing enough
// return 0 for not done, 1 for done
// if any one philo has not eaten enough, not done
// if done 
//printf("%s\n", "every philos has eaten enough");
//uint64_t	timestamp;
//timestamp = now_ms() - table->starting_time;
//pthread_mutex_lock(&table->printf_lock);
//printf("%llu all philos ate enough times\n", (unsigned long long)timestamp);
//pthread_mutex_unlock(&table->printf_lock);
static int	check_done(t_table *table)
{
	int			i;
	int			meals;

	i = 1;
	if (table->total_eating_time == -1)
		return (0);
	while (i <= table->nbr)
	{
		pthread_mutex_lock(&table->state_lock);
		meals = table->philos[i].meals_eaten;
		pthread_mutex_unlock(&table->state_lock);
		if (meals < table->total_eating_time)
			return (0);
		i++;
	}
	if (!ft_is_stoped(table))
	{
		pthread_mutex_lock(&table->state_lock);
		table->stop = 1;
		pthread_mutex_unlock(&table->state_lock);
		pthread_mutex_lock(&table->printf_lock);
		printf("%s\n", "every philos has eaten enough");
		pthread_mutex_unlock(&table->printf_lock);
	}
	return (1);
}

// check if any philo is dead from staring
// return 1 for dead and 0 for not
static int	check_dead(t_table *table)
{
	int			i;
	uint64_t	last_time;

	if (ft_is_stoped(table))
		return (0);
	i = 1;
	while (i <= table->nbr)
	{
		pthread_mutex_lock(&table->state_lock);
		last_time = table->philos[i].last_eating_time;
		pthread_mutex_unlock(&table->state_lock);
		if (!ft_is_stoped(table)
			&& (now_ms() - last_time >= (uint64_t)table->to_die_time))
		{
			pthread_mutex_lock(&table->state_lock);
			table->stop = 1;
			pthread_mutex_unlock(&table->state_lock);
			pthread_mutex_lock(&table->printf_lock);
			printf("%lu %d died\n", (now_ms() - table->starting_time), i);
			pthread_mutex_unlock(&table->printf_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

// call this in init
void	*monitor(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	while (1)
	{
		if (check_done(table))
			break ;
		if (check_dead(table))
			break ;
		usleep(1000);
	}
	return (NULL);
}

// if (!philo_table)
// 	return (-1);
int	main(int argc, char **argv)
{
	t_table	*philo_table;

	if (!pre_check_argv(argc, argv))
		return (-1);
	philo_table = init_table(argv);
	ft_free_table(philo_table);
	return (0);
}
