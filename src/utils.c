/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuwu <yuwu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:08:28 by yuwu              #+#    #+#             */
/*   Updated: 2025/09/07 15:02:05 by yuwu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// struct timeval {
//     time_t      tv_sec;   // s
//     suseconds_t tv_usec;  // 1µs (1µs = 10^-6 s)
// };
// gettimeofday, settimeofday - get / set time
//     --> return the time on the wall in millisecond, "real-world time"
// I am going to use MACROSECOND,  us in my philosopher
uint64_t	now_ms(void)
{
	struct timeval	current_time;
	uint64_t		time_ms;

	gettimeofday(&current_time, NULL);
	time_ms = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time_ms);
}

// do a sleep
void	smart_usleep(uint64_t duration, t_table *table)
{
	uint64_t	start;

	start = now_ms();
	while (now_ms() - start < duration)
	{
		if (ft_is_stoped(table))
			break ;
		usleep(100);
	}
}

void	get_fork_nbr(t_philo *philo, int *first, int *second)
{
	if (philo->id % 2)
	{
		*first = philo->fork_l;
		*second = philo->fork_r;
	}
	else
	{
		*first = philo->fork_r;
		*second = philo->fork_l;
	}
}

// return 1 on getting fork and 0 on not getting
int	pick_one_fork(t_philo *philo, int fork_id)
{
	pthread_mutex_lock(&philo->table->forks[fork_id]);
	if (ft_is_stoped(philo->table))
	{
		pthread_mutex_unlock(&philo->table->forks[fork_id]);
		return (0);
	}
	pthread_mutex_lock(&philo->table->printf_lock);
	if (!ft_is_stoped(philo->table))
	{
		printf("%llu %d has taken a fork\n", (unsigned long long)(now_ms() -
			philo->table->starting_time), philo->id);
	}
	pthread_mutex_unlock(&philo->table->printf_lock);
	if (ft_is_stoped(philo->table))
	{
		pthread_mutex_unlock(&philo->table->forks[fork_id]);
		return (0);
	}
	return (1);
}

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
