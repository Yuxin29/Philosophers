/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuwu <yuwu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:08:19 by yuwu              #+#    #+#             */
/*   Updated: 2025/09/01 20:11:33 by yuwu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//return 0 as not doing anything
static int	take_forks_and_check(t_philo *philo, int *first, int *second)
{
	if (philo->fork_r == -1)
		return (0);
	if (philo->fork_l < philo->fork_r)
	{
		*first = philo->fork_l;
		*second = philo->fork_r;
	}
	else
	{
		*first = philo->fork_r;
		*second = philo->fork_l;
	}
	pthread_mutex_lock(&philo->table->forks[*first]);
	pthread_mutex_lock(&philo->table->forks[*second]);
	if (ft_is_stoped(philo->table))
	{
		pthread_mutex_unlock(&philo->table->forks[*second]);
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

	if (!take_forks_and_check(philo, &first, &second))
		return ;
	pthread_mutex_lock(&philo->table->state_lock);
	philo->last_eating_time = now_ms();
	philo->meals_eaten += 1;
	pthread_mutex_unlock(&philo->table->state_lock);
	timestamp = now_ms() - philo->table->starting_time;
	pthread_mutex_lock(&philo->table->printf_lock);
	printf("%lu, %d is eating\n", timestamp, philo->id + 1);
	pthread_mutex_unlock(&philo->table->printf_lock);
	ft_to_eat(philo->table);
	pthread_mutex_unlock(&philo->table->forks[second]);
	pthread_mutex_unlock(&philo->table->forks[first]);
}

// sleep a certain time
static void	routine_sleep(t_philo *philo)
{
	uint64_t	timestamp;

	if (ft_is_stoped(philo->table))
		return ;
	timestamp = now_ms() - philo->table->starting_time;
	pthread_mutex_lock(&philo->table->printf_lock);
	printf("%lu, %d is sleeping\n", timestamp, philo->id + 1);
	pthread_mutex_unlock(&philo->table->printf_lock);
	ft_to_sleep(philo->table);
}

// in pholosopher, there is not given time for think
// it does not uslepp. just print a msg
static void	routine_think(t_philo *philo)
{
	uint64_t	timestamp;

	if (ft_is_stoped(philo->table))
		return ;
	timestamp = now_ms() - philo->table->starting_time;
	pthread_mutex_lock(&philo->table->printf_lock);
	printf("%lu, %d is thinking\n", timestamp, philo->id + 1);
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
	if (philo->id % 2)
		usleep(500);
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
		usleep(50);
	}
	return (NULL);
}
