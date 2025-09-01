/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuwu <yuwu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:07:54 by yuwu              #+#    #+#             */
/*   Updated: 2025/09/01 20:20:35 by yuwu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// precheck stop,
// need to prptect the stop shen check, 
// because it might be changed by other thrd
// return 1 for stop and 0 for not
int	ft_is_stoped(t_table *table)
{
	int	stop;

	pthread_mutex_lock(&table->state_lock);
	stop = table->stop;
	pthread_mutex_unlock(&table->state_lock);
	return (stop);
}

// check if all philo has eateing enough
// return 0 for not done, 1 for done
// if any one philo has not eaten enough, not done
// if done 
static int	check_done(t_table *table)
{
	int			i;
	int			n;
	uint64_t	timestamp;

	i = 0;
	if (table->total_eating_time == -1)
		return (0);
	while (i < table->nbr)
	{
		if (table->philos[i].meals_eaten < table->total_eating_time)
			return (0);
		i++;
	}
	if (!ft_is_stoped(table))
	{
		pthread_mutex_lock(&table->state_lock);
			table->stop = 1;
		pthread_mutex_unlock(&table->state_lock);
		timestamp = now_ms() - table->starting_time;
		n = table->total_eating_time;
		pthread_mutex_lock(&table->printf_lock);
		printf("%lu, all philos ate %d times (enough)\n", timestamp, n);
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
	i = 0;
	while (i < table->nbr)
	{
		pthread_mutex_lock(&table->state_lock);
		last_time = table->philos[i].last_eating_time;
		pthread_mutex_unlock(&table->state_lock);
		if ((now_ms() - last_time) >= (uint64_t)table->to_die_time)
		{
			if (!ft_is_stoped(table))
			{
				pthread_mutex_lock(&table->state_lock);
				table->dead = 1;
				table->stop = 1;
				pthread_mutex_unlock(&table->state_lock);
				pthread_mutex_lock(&table->printf_lock);
				printf("%lu, %d died\n", (now_ms() - table->starting_time), i + 1);
				pthread_mutex_unlock(&table->printf_lock);
			}
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
		if (ft_is_stoped(table))
			break ;
		if (check_done(table))
			break ;
		if (check_dead(table))
			break ;
		usleep(500);
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
