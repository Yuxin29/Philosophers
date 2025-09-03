/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuwu <yuwu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:08:28 by yuwu              #+#    #+#             */
/*   Updated: 2025/09/03 11:25:15 by yuwu             ###   ########.fr       */
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
void	ft_to_sleep(t_table *table)
{
	uint64_t	start;
	useconds_t	duration;

	start = now_ms();
	duration = table->sleep_time;
	while (!table->stop && (now_ms() - start) < duration)
		usleep(50);
}

// do a eat
void	ft_to_eat(t_table *table)
{
	uint64_t	start;
	useconds_t	duration;

	start = now_ms();
	duration = table->eat_time;
	while (!table->stop && (now_ms() - start) < duration)
		usleep(50);
}
