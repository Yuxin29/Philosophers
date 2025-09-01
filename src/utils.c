/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuwu <yuwu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:08:28 by yuwu              #+#    #+#             */
/*   Updated: 2025/09/01 18:08:55 by yuwu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// I am going to use millisecond,  毫秒 in my philosopher
// struct timeval {
//     time_t      tv_sec;   // s
//     suseconds_t tv_usec;  // 1µs (1µs = 10^-6 s)
// };
// gettimeofday, settimeofday - get / set time
//     --> return the time on the wall in millisecond, "real-world time"
uint64_t	now_ms(void)
{
	struct timeval	current_time;
	uint64_t		time_ms;

	if (gettimeofday(&current_time, NULL) == -1)
		return (0);
	time_ms = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time_ms);
}

// do a sleep
void	ft_to_sleep(t_table *table)
{
	useconds_t	sleep_period;

	sleep_period = table->sleep_time * 1000;
	usleep(sleep_period);
	return ;
}

// do a eat
void	ft_to_eat(t_table *table)
{
	useconds_t	eating_period;

	eating_period = table->eat_time * 1000;
	usleep(eating_period);
	return ;
}

// free the table and philos, and destroy all the mutex
void	ft_free_table(t_table *table)
{
	int	i;

	i = 0;
	if (!table)
		return ;
	if (table->philos)
		free(table->philos);
	if (table->forks)
	{
		while (i < table->nbr)
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
