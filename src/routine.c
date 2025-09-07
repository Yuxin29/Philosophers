/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuwu <yuwu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:08:19 by yuwu              #+#    #+#             */
/*   Updated: 2025/09/07 17:41:08 by yuwu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// pick up 2 forks
// situation of single philo / single fork checked first
static int	pickup_forks(t_philo *philo, int *first, int *second)
{
	if (philo->fork_r == -1)
	{
		if (!pick_one_fork(philo, philo->fork_l))
			return (0);
		smart_usleep(philo->table->to_die_time, philo->table);
		pthread_mutex_unlock(&philo->table->forks[philo->fork_l]);
		return (0);
	}
	get_fork_nbr(philo, first, second);
	if (!pick_one_fork(philo, *first))
		return (0);
	if (!pick_one_fork(philo, *second))
	{
		pthread_mutex_unlock(&philo->table->forks[*first]);
		return (0);
	}
	return (1);
}

// eating steps of a philo
// pick up 2 forks(lock them) --> eat --> update stts -> unlock forks
static void	routine_eat(t_philo *philo)
{
	uint64_t	timestamp;
	int			first;
	int			second;

	if (philo->id % 2 == 0)
		usleep(500);
	if (!pickup_forks(philo, &first, &second))
		return ;
	pthread_mutex_lock(&philo->table->state_lock);
	philo->last_eating_time = now_ms();
	philo->meals_eaten += 1;
	pthread_mutex_unlock(&philo->table->state_lock);
	pthread_mutex_lock(&philo->table->printf_lock);
	if (!ft_is_stoped(philo->table))
	{
		timestamp = now_ms() - philo->table->starting_time;
		printf("%lu %d is eating\n", timestamp, philo->id);
	}
	pthread_mutex_unlock(&philo->table->printf_lock);
	smart_usleep(philo->table->eat_time, philo->table);
	pthread_mutex_unlock(&philo->table->forks[second]);
	pthread_mutex_unlock(&philo->table->forks[first]);
}

// sleep a certain time
static void	routine_sleep(t_philo *philo)
{
	uint64_t	timestamp;

	pthread_mutex_lock(&philo->table->printf_lock);
	if (!ft_is_stoped(philo->table))
	{
		timestamp = now_ms() - philo->table->starting_time;
		printf("%lu %d is sleeping\n", timestamp, philo->id);
	}
	pthread_mutex_unlock(&philo->table->printf_lock);
	smart_usleep(philo->table->sleep_time, philo->table);
}

// in pholosopher, there is not given time for think
// it does not uslepp. just print a msg
static void	routine_think(t_philo *philo)
{
	uint64_t	timestamp;

	pthread_mutex_lock(&philo->table->printf_lock);
	if (!ft_is_stoped(philo->table))
	{
		timestamp = now_ms() - philo->table->starting_time;
		printf("%lu %d is thinking\n", timestamp, philo->id);
	}
	pthread_mutex_unlock(&philo->table->printf_lock);
}

// routine of a philo: eat --> sleep --> think
// usleep(1000); 1 ms
void	*routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (philo->fork_r == -1)
	{
		routine_eat(philo);
		return (NULL);
	}
	usleep(1000);
	while (1)
	{
		if (ft_is_stoped(philo->table))
			break ;
		routine_eat(philo);
		if (ft_is_stoped(philo->table))
			break ;
		routine_sleep(philo);
		if (ft_is_stoped(philo->table))
			break ;
		routine_think(philo);
		usleep(1000);
	}
	return (NULL);
}
